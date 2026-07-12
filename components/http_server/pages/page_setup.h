/* Getting Started page templates */
#include "router_config.h"

#if !CONFIG_ETH_UPLINK
/* Getting Started Page */
#define SETUP_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>AeroLink — Setup</title>\
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
@keyframes pulse{0%,100%{opacity:0.6;}50%{opacity:1;}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.ok-btn{transition:all 0.3s ease,box-shadow 0.3s;}\
.ok-btn:hover{box-shadow:0 0 12px rgba(100,149,237,0.25);}\
.nav-link{transition:all 0.3s ease;}\
.nav-link:hover{box-shadow:0 0 10px rgba(100,149,237,0.2);}\
table{width:100%%;border-collapse:collapse;}\
td{padding:0.4rem 0;vertical-align:top;}\
td:first-child{color:#555;font-size:0.75rem;padding-right:0.75rem;width:35%%;text-align:right;text-transform:uppercase;letter-spacing:0.5px;}\
input[type='text'],input[type='password']{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:8px;color:#fff;padding:0.6rem;font-size:0.85rem;transition:all 0.3s;box-sizing:border-box;overflow:hidden;}\
input:focus{outline:none;border-color:rgba(255,255,255,0.2);}\
input::placeholder{color:#333;}\
.ok-btn{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.6rem;font-size:0.85rem;cursor:pointer;width:100%%;margin-top:0.3rem;transition:all 0.3s;}\
.ok-btn:hover{background:rgba(255,255,255,0.14);}\
.nav-link{display:inline-block;padding:0.5rem 1rem;background:rgba(255,255,255,0.04);color:#888;border:1px solid rgba(255,255,255,0.06);border-radius:8px;text-decoration:none;font-size:0.8rem;margin:0.3rem;transition:all 0.3s;}\
.nav-link:hover{background:rgba(255,255,255,0.08);color:#fff;}\
@media(max-width:600px){body{padding:1rem;}td:first-child{font-size:0.7rem;width:40%%;}}\
</style>\
<body>\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — Setup</h1>\
<script>\
var qs=window.location.search.substr(1);\
if(qs.indexOf('ap_ssid=')!==-1||(qs.indexOf('ssid=')!==-1&&qs.indexOf('password=')!==-1)){\
document.getElementById('wrap').innerHTML='<h1>AeroLink — Setup</h1><div class=\"glass\"><p style=\"text-align:center;color:#888;\">Saved. Rebooting...</p></div>';\
setTimeout(\"location.href='/'\",8000);}\
</script>"

/* Setup form */
#define SETUP_CHUNK_FORM "\
<div class='glass'>\
<h2>Access Point</h2>\
<form action='/setup' method='GET'>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ap_ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' name='ap_password'/></td></tr>\
</table>\
<h2>Uplink</h2>\
<table>\
<tr><td>SSID</td><td><input type='text' name='ssid' value='%s'/></td></tr>\
<tr><td>Password</td><td><input type='password' name='password'/></td></tr>\
<tr><td></td><td><input type='submit' value='Save & Reboot' class='ok-btn'/></td></tr>\
</table></form></div>\
<div style='text-align:center;margin-top:1rem;'>\
<a href='/scan' class='nav-link'>📡 Scan</a>\
<a href='/' class='nav-link'>← Home</a>\
</div></div></body></html>"
#endif /* !CONFIG_ETH_UPLINK */
