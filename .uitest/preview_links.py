"""Preview-only helper (never touches the firmware templates).

The preview pane serves exactly one registered HTML file, so sibling pages
like /setup cannot be fetched over HTTP. This script therefore:

1. injects a click interceptor into every rendered sample (it forwards
   internal navigation to the parent bundle when running inside an iframe,
   otherwise falls back to plain file navigation), and
2. builds .uitest/out/preview.html - a single self-contained bundle that
   embeds all six pages as srcdoc iframes, so every nav option in the
   preview works with zero server requests.
"""
import glob
import json
import os

NAV = (
    "<script>(function(){"
    "var map={'/':'index.html','/setup':'setup.html','/scan':'scan.html',"
    "'/config':'config.html','/mappings':'mappings.html','/firewall':'firewall.html'};"
    "document.addEventListener('click',function(e){"
    "var a=e.target&&e.target.closest?e.target.closest('a[href]'):null;"
    "if(!a)return;"
    "var h=a.getAttribute('href')||'';"
    "if(h.charAt(0)!=='/'&&h.charAt(0)!=='?')return;"
    "var path=h.split('?')[0];"
    "var target=map[path]||(path==='/'?'index.html':null);"
    "if(!target)return;"
    "e.preventDefault();"
    "if(window.self!==window.top){window.parent.postMessage({pv:target},'*');}"
    "else{location.href=target;}"
    "},false);"
    "})();"
    "</script>"
)

pages = {}
for f in sorted(glob.glob(".uitest/out/*.html")):
    name = os.path.basename(f)
    if name == "preview.html":
        continue
    html = open(f, encoding="utf-8").read()
    if "window.parent.postMessage({pv:" not in html:
        idx = html.rfind("</body>")
        if idx == -1:
            idx = len(html)
        html = html[:idx] + NAV + html[idx:]
        open(f, "w", encoding="utf-8").write(html)
    pages[name] = html

# Page HTML contains literal </script> tags (every page has inline JS).
# A raw </script> inside a JS string terminates the embedding <script>
# element, so the JSON breaks out and page source leaks into the document.
# Escaping the slash ("<\/" === "</" in JS) keeps the script element intact.
pages_json = json.dumps(pages).replace("</", "<\\/")

bundle = (
    "<!doctype html><html lang='en'><head><meta charset='utf-8'>"
    "<meta name='viewport' content='width=device-width,initial-scale=1'>"
    "<title>AeroLink UI preview</title>"
    "<style>html,body{margin:0;height:100%;background:#000;}"
    "iframe{border:0;width:100%;height:100%;display:block;}</style>"
    "</head><body>"
    "<iframe id='f' title='AeroLink page'></iframe>"
    "<script>var PAGES=" + pages_json + ";"
    "var f=document.getElementById('f');"
    "function show(n){if(!PAGES[n])n='index.html';f.srcdoc=PAGES[n];"
    "document.title='AeroLink - '+n;}"
    "window.addEventListener('message',function(e){"
    "if(e.data&&e.data.pv){show(e.data.pv);history.replaceState(null,'','#'+e.data.pv);}});"
    "show((location.hash||'').slice(1)||'index.html');"
    "</script></body></html>"
)
open(".uitest/out/preview.html", "w", encoding="utf-8").write(bundle)
print("bundle built:", len(pages), "pages ->", len(bundle), "bytes")
