/* WiFi Scan page templates */
#include "router_config.h"

#if !CONFIG_ETH_UPLINK
/* WiFi Scan Page.
 * IMPORTANT: SCAN_PAGE is passed straight to snprintf() as the format string
 * (refresh seconds, network count, action column, result rows), so every
 * literal percent sign in this template MUST be written as %%. */
#define SCAN_PAGE "<!doctype html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,initial-scale=1'>\
<meta name='color-scheme' content='dark'>\
<meta name='theme-color' content='#000000'>\
<meta http-equiv='refresh' content='%d'>\
<title>AeroLink - Scan</title>\
<link rel='icon' href='/favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap' rel='stylesheet'>\
<style>\
*{box-sizing:border-box;margin:0;padding:0}\
html{-webkit-text-size-adjust:100%%}\
body{font-family:'Inter',system-ui,-apple-system,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;background:#000;color:#eef1f6;color-scheme:dark;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:1.1rem 1rem calc(1.5rem + env(safe-area-inset-bottom))}\
body::before{content:'';position:fixed;inset:0;z-index:0;pointer-events:none;background:radial-gradient(700px 340px at 50%% -120px,rgba(79,140,255,.22),transparent 70%%),radial-gradient(520px 420px at 110%% 110%%,rgba(79,140,255,.07),transparent 70%%)}\
#wrap{position:relative;z-index:1;width:100%%;max-width:660px;margin:auto}\
a{color:#7fa9ff;text-decoration:none}\
a:hover{color:#aecbff}\
:focus-visible{outline:2px solid rgba(127,169,255,.8);outline-offset:2px}\
::selection{background:rgba(79,140,255,.35)}\
.topbar{display:flex;align-items:center;justify-content:space-between;min-height:32px;margin-bottom:.3rem}\
.brand{display:inline-flex;align-items:center;gap:.55rem;color:#e7ecf5;font-size:.74rem;font-weight:600;letter-spacing:.22em;text-transform:uppercase}\
:root{--logo:url(\"data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 64 64'><rect width='64' height='64' rx='15' fill='rgb(7,11,20)'/><path d='M18 47 32 17 46 47' fill='none' stroke='rgb(79,140,255)' stroke-width='6.5' stroke-linecap='round' stroke-linejoin='round'/><path d='M24.5 37.5h15' stroke='rgb(79,140,255)' stroke-width='6.5' stroke-linecap='round'/></svg>\")}\
.brand .logo{display:inline-block;width:24px;height:24px;border-radius:7px;background:#070b14 var(--logo) center/62%% no-repeat;box-shadow:0 0 0 1px rgba(255,255,255,.14);overflow:hidden;flex:none}\
.brand .logo img{display:block;width:100%%;height:100%%;object-fit:contain}\
.brand:hover{color:#fff}\
h1{font-size:1.3rem;font-weight:600;letter-spacing:-.01em;margin:.2rem 0 .1rem}\
.nav{display:flex;flex-wrap:wrap;gap:.38rem;margin:.7rem 0 1rem}\
.nav a{font-size:.7rem;font-weight:500;letter-spacing:.05em;color:#98a1ae;padding:.42rem .78rem;border-radius:999px;border:1px solid rgba(255,255,255,.09);background:rgba(255,255,255,.035);transition:color .18s,border-color .18s,background .18s}\
.nav a:hover{color:#fff;border-color:rgba(127,169,255,.5);background:rgba(79,140,255,.14)}\
.nav a.on{color:#dce9ff;border-color:rgba(79,140,255,.55);background:rgba(79,140,255,.17)}\
.sub{color:#7b8391;font-size:.74rem;letter-spacing:.05em;margin:-.5rem 0 1.1rem}\
.sub b{color:#c3cad5;font-weight:600}\
@keyframes rise{from{opacity:0;transform:translateY(14px)}to{opacity:1;transform:none}}\
@keyframes pulse{0%%,100%%{opacity:.5}50%%{opacity:1}}\
.glass{background:linear-gradient(165deg,rgba(255,255,255,.055),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.09);border-radius:18px;padding:1.2rem;backdrop-filter:blur(18px) saturate(150%%);-webkit-backdrop-filter:blur(18px) saturate(150%%);box-shadow:0 12px 40px rgba(0,0,0,.5),inset 0 1px 0 rgba(255,255,255,.05);margin-bottom:1rem;overflow-x:auto;animation:rise .5s cubic-bezier(.2,.7,.3,1) both}\
.tbl{width:100%%;border-collapse:collapse}\
.tbl th{font-size:.62rem;font-weight:600;letter-spacing:.12em;text-transform:uppercase;color:#7b8391;text-align:left;padding:.6rem .55rem;border-bottom:1px solid rgba(255,255,255,.09);white-space:nowrap}\
.tbl td{padding:.65rem .55rem;font-size:.82rem;color:#cfd5de;border-bottom:1px solid rgba(255,255,255,.05);vertical-align:middle}\
.tbl tbody tr:last-child td{border-bottom:none}\
.tbl tbody tr:hover td{background:rgba(255,255,255,.03)}\
.tbl td:first-child{color:#eef1f6;font-weight:500;max-width:200px;overflow:hidden;text-overflow:ellipsis;white-space:nowrap}\
.tbl td[colspan]{text-align:center!important;color:#7b8391!important}\
.tbl td[colspan] span{color:#8ab4ff!important}\
.signal-bars{display:inline-flex;align-items:flex-end;gap:2px;height:16px;vertical-align:middle;margin-right:.15rem}\
.signal-bars .bar{width:3.5px;border-radius:2px;background:rgba(255,255,255,.1)}\
.signal-bars .bar.active.signal-excellent{background:#a5c4ff}\
.signal-bars .bar.active.signal-good{background:#7aa5ff}\
.signal-bars .bar.active.signal-fair{background:#4f8cff}\
.signal-bars .bar.active.signal-weak{background:#3563c4}\
.signal-bars .bar.active.signal-poor{background:#6b7280}\
.connect-button{display:inline-block;padding:.34rem .8rem;border-radius:8px;border:1px solid rgba(79,140,255,.55);background:linear-gradient(180deg,#4f8cff,#3b74de);color:#fff;font-size:.72rem;font-weight:600;letter-spacing:.04em;transition:filter .15s,transform .1s}\
.connect-button:hover{filter:brightness(1.1);color:#fff}\
.connect-button:active{transform:translateY(1px)}\
@media(max-width:640px){\
body{padding:.9rem .75rem calc(1.2rem + env(safe-area-inset-bottom))}\
.glass{padding:1rem .8rem;border-radius:16px}\
h1{font-size:1.15rem}\
.tbl{min-width:560px}\
}\
@media(prefers-reduced-motion:reduce){*{animation-duration:.01ms!important;animation-iteration-count:1!important;transition-duration:.01ms!important}}\
::-webkit-scrollbar{width:10px;height:10px}\
::-webkit-scrollbar-thumb{background:rgba(255,255,255,.14);border-radius:8px}\
::-webkit-scrollbar-track{background:transparent}\
</style>\
<script>window.addEventListener('error',function(e){if(e.target&&e.target.tagName=='IMG'){e.target.style.display='none';}},true);</script>\
</head>\
<body>\
<div id='wrap'>\
<div class='topbar'><a class='brand' href='/'><span class='logo'><img src='/favicon.png' alt=''></span><span>AeroLink</span></a></div>\
<h1>Wi-Fi Scan</h1>\
<nav class='nav' aria-label='Sections'>\
<a href='/'>Home</a>\
<a href='/setup'>Setup</a>\
<a href='/scan' class='on'>Scan</a>\
<a href='/config'>Config</a>\
<a href='/mappings'>Mappings</a>\
<a href='/firewall'>Firewall</a>\
</nav>\
<div class='sub'><span id='rn'>Auto-refreshing</span> &middot; <b>%d networks found</b></div>\
<div class='glass'>\
<table class='tbl'>\
<thead><tr><th>SSID</th><th>Signal</th><th>Ch</th><th>Security</th>%s</tr></thead>\
<tbody>%s</tbody>\
</table>\
</div>\
</div>\
<script>\
(function(){var m=document.querySelector('meta[http-equiv=refresh]');var n=document.getElementById('rn');if(m&&n&&m.content){n.textContent='Refreshing every '+m.content+' seconds';}})();\
(function(){var y=0;try{y=sessionStorage.getItem('scanY')||0;}catch(e){}if(y>0){window.scrollTo(0,+y);}var t=0;window.addEventListener('scroll',function(){clearTimeout(t);t=setTimeout(function(){try{sessionStorage.setItem('scanY',window.scrollY);}catch(e){}},150);},{passive:true});})();\
</script>\
</body></html>"
#endif /* !CONFIG_ETH_UPLINK */
