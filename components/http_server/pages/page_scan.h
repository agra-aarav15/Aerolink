/* WiFi Scan page templates */
#include "router_config.h"

#if !CONFIG_ETH_UPLINK
/* WiFi Scan Page */
#define SCAN_PAGE "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<meta http-equiv='refresh' content='%d'>\
<title>AeroLink — Scan</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.5rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:600px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;letter-spacing:3px;text-transform:uppercase;margin-bottom:0.3rem;}\
.sub{color:#555;font-size:0.7rem;letter-spacing:1px;margin-bottom:1.5rem;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.5rem;margin-bottom:1rem;overflow-x:auto;}\
a.home{display:inline-flex;align-items:center;gap:0.5rem;color:#555;text-decoration:none;font-size:0.75rem;margin-bottom:1.5rem;transition:color 0.3s;}\
a.home:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
@keyframes pulse{0%,100%{opacity:0.6;}50%{opacity:1;}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.tbl tbody tr{animation:fadeIn 0.3s ease-out both;}\
.tbl tbody tr:nth-child(odd){animation-delay:0.05s;}\
.tbl tbody tr:nth-child(even){animation-delay:0.1s;}\
.sbar .b.on{animation:pulse 2s ease-in-out infinite;}\
.cbtn{transition:all 0.3s ease,box-shadow 0.3s;}\
.cbtn:hover{box-shadow:0 0 10px rgba(100,149,237,0.2);}\
.tbl{width:100%%;border-collapse:collapse;margin-top:0.5rem;}\
.tbl th{font-size:0.65rem;font-weight:600;color:#555;text-transform:uppercase;letter-spacing:1px;text-align:left;padding:0.5rem;border-bottom:1px solid rgba(255,255,255,0.06);}\
.tbl td{padding:0.5rem;font-size:0.8rem;color:#ccc;border-bottom:1px solid rgba(255,255,255,0.03);}\
.tbl tbody tr:hover td{background:rgba(255,255,255,0.03);}\
.sbar,.signal-bars{display:inline-flex;align-items:flex-end;gap:2px;height:16px;vertical-align:middle;}\
.sbar .b,.signal-bars .bar{width:3px;border-radius:1px;background:rgba(255,255,255,0.1);}\
.sbar .b.on.e,.signal-bars .bar.active.signal-excellent{background:#4caf50;}\
.sbar .b.on.g,.signal-bars .bar.active.signal-good{background:#8bc34a;}\
.sbar .b.on.f,.signal-bars .bar.active.signal-fair{background:#ffc107;}\
.sbar .b.on.w,.signal-bars .bar.active.signal-weak{background:#ff9800;}\
.sbar .b.on.p,.signal-bars .bar.active.signal-poor{background:#f44336;}\
.cbtn{background:rgba(255,255,255,0.06);color:#fff;border:1px solid rgba(255,255,255,0.08);border-radius:8px;padding:0.3rem 0.7rem;font-size:0.7rem;font-weight:500;cursor:pointer;text-decoration:none;transition:all 0.3s;}\
.cbtn:hover{background:rgba(255,255,255,0.12);}\
@media(max-width:600px){body{padding:1rem;}.tbl th,.tbl td{padding:0.3rem;font-size:0.7rem;}}\
</style>\
<body>\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — Scan</h1>\
<div class='sub'>Auto-refresh %d networks</div>\
<div class='glass'>\
<table class='tbl'>\
<thead><tr><th>SSID</th><th>Signal</th><th>Ch</th><th>Security</th>%s</tr></thead>\
<tbody>%s</tbody>\
</table>\
</div>\
</div></body></html>"
#endif /* !CONFIG_ETH_UPLINK */
