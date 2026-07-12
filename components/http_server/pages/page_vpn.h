/* VPN page templates */
/* VPN Page - Chunked for streaming */
#define VPN_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>AeroLink — VPN</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.5rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:520px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;letter-spacing:3px;text-transform:uppercase;margin-bottom:0.3rem;}\
h2{font-size:0.7rem;font-weight:600;color:#555;text-transform:uppercase;letter-spacing:2px;margin:1.5rem 0 0.8rem;border-bottom:1px solid rgba(255,255,255,0.05);padding-bottom:0.5rem;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.5rem;margin-bottom:1rem;}\
a.home{display:inline-flex;align-items:center;gap:0.5rem;color:#555;text-decoration:none;font-size:0.75rem;margin-bottom:1.5rem;transition:color 0.3s;}\
a.home:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
@keyframes glow{0%,100%{box-shadow:0 0 8px rgba(100,149,237,0.15);}50%{box-shadow:0 0 18px rgba(100,149,237,0.3);}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.glass:nth-child(2){animation-delay:0.08s;}\
.glass:nth-child(3){animation-delay:0.16s;}\
.ok-btn{transition:all 0.3s ease,box-shadow 0.3s;}\
.ok-btn:hover{box-shadow:0 0 12px rgba(100,149,237,0.25);}\
textarea{transition:border-color 0.3s;}\
textarea:focus{animation:glow 2s ease-in-out infinite;}\
table{width:100%%;border-collapse:collapse;}\
td{padding:0.4rem 0;vertical-align:top;}\
td:first-child{color:#555;font-size:0.75rem;padding-right:0.75rem;width:35%%;text-align:right;text-transform:uppercase;letter-spacing:0.5px;}\
input[type='text'],input[type='number'],input[type='password']{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.85rem;transition:all 0.3s;box-sizing:border-box;overflow:hidden;}\
input:focus{outline:none;border-color:rgba(255,255,255,0.2);}\
input::placeholder{color:#333;}\
textarea{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.8rem;font-family:monospace;resize:vertical;box-sizing:border-box;}\
textarea:focus{outline:none;border-color:rgba(255,255,255,0.2);}\
textarea::placeholder{color:#333;}\
select{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.85rem;-webkit-appearance:none;box-sizing:border-box;overflow:hidden;}\
select option{background:#111;color:#fff;}\
.ok-btn{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.6rem;font-size:0.85rem;cursor:pointer;width:100%%;margin-top:0.3rem;}\
.ok-btn:hover{background:rgba(255,255,255,0.14);}\
.stbl{background:rgba(255,255,255,0.02);border-radius:12px;padding:1rem;margin:1rem 0;border:1px solid rgba(255,255,255,0.04);}\
.stbl table{width:100%%;}\
.stbl td{padding:0.5rem;font-size:0.82rem;border-bottom:1px solid rgba(255,255,255,0.03);}\
.stbl tr:last-child td{border-bottom:none;}\
.stbl td:first-child{color:#444;text-align:right;width:40%%;font-size:0.75rem;}\
small{display:block;color:#333;font-size:0.7rem;margin-top:0.3rem;}\
@media(max-width:600px){body{padding:1rem;}td:first-child{font-size:0.7rem;width:40%%;}}\
</style>\
<body>\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — VPN</h1>"

#define VPN_CHUNK_MID "\
<script>\
var qs=window.location.search.substr(1);\
if(qs.indexOf('vpn_enabled=')!==-1||qs.indexOf('vpn_privkey=')!==-1){\
document.getElementById('wrap').innerHTML='<h1>AeroLink — VPN</h1><div class=\"glass\"><p style=\"text-align:center;color:#888;\">Saved. Rebooting...</p></div>';\
setTimeout(\"location.href='/'\",8000);}\
</script>"

#define VPN_CHUNK_IMPORT "\
<div class='glass'>\
<h2>Import Config</h2>\
<p style='color:#444;font-size:0.75rem;margin-bottom:0.5rem;'>Paste WireGuard .conf</p>\
<textarea id='wgconf' rows='8' placeholder='[Interface]&#10;PrivateKey = ...&#10;Address = 10.2.0.2/32&#10;&#10;[Peer]&#10;PublicKey = ...&#10;Endpoint = host:51820&#10;AllowedIPs = 0.0.0.0/0'></textarea>\
<button type='button' class='ok-btn' onclick='importWg()'>Import & Reboot</button>\
<div id='wgmsg' style='margin-top:0.3rem;font-size:0.8rem;color:#888;'></div>\
<script>\
function importWg(){\
var t=document.getElementById('wgconf').value;var m=document.getElementById('wgmsg');\
if(!t.trim()){m.textContent='Paste a config';return;}\
m.textContent='Importing...';\
fetch('/api/vpn-import',{method:'POST',body:t}).then(function(r){return r.json();}).then(function(d){\
if(d.ok){m.style.color='#4caf50';m.textContent=d.msg;setTimeout(function(){location.href='/';},8000);}\
else{m.style.color='#f44336';m.textContent=d.msg||'Failed';}\
}).catch(function(){m.style.color='#f44336';m.textContent='Error';});}\
</script></div>"

#define VPN_CHUNK_FORM_OPEN "\
<div class='glass'>\
<h2>Configuration</h2>\
<form action='/vpn' method='GET'>\
<table>"

#define VPN_CHUNK_FORM_CLOSE "\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table></form></div>"

#define VPN_CHUNK_PAGE_END "\
<div style='text-align:center;margin-top:1.5rem;'><a href='/' style='color:#555;text-decoration:none;font-size:0.8rem;'>← Home</a></div>\
</div></body></html>"
