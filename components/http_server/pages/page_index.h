/* Index page templates */
#include "router_config.h"

#if CONFIG_ETH_UPLINK
#define INDEX_TITLE "AeroLink (LAN)"
#else
#define INDEX_TITLE "AeroLink"
#endif

/* Index Page - Chunked for streaming */
#define INDEX_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>" INDEX_TITLE "</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.5rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:520px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;text-align:center;margin-bottom:0.3rem;letter-spacing:3px;text-transform:uppercase;}\
.sub{text-align:center;color:#555;font-size:0.7rem;margin-bottom:2rem;letter-spacing:1px;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.5rem;margin-bottom:1rem;}\
.glass h2{font-size:0.7rem;font-weight:600;color:#888;text-transform:uppercase;letter-spacing:2px;margin-bottom:1rem;}\
.tbl{width:100%;border-collapse:collapse;}\
.tbl td{padding:0.6rem 0.5rem;font-size:0.82rem;border-bottom:1px solid rgba(255,255,255,0.04);}\
.tbl tr:last-child td{border-bottom:none;}\
.tbl td:first-child{color:#666;text-align:right;padding-right:1rem;width:40%;font-size:0.75rem;text-transform:uppercase;letter-spacing:0.5px;}\
.tbl td:last-child{color:#ddd;font-weight:400;}\
.grid{display:grid;grid-template-columns:1fr 1fr;gap:0.75rem;margin-top:0.5rem;}\
.btn{display:flex;align-items:center;justify-content:center;gap:0.6rem;padding:1rem;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.06);border-radius:12px;color:#fff;text-decoration:none;font-size:0.82rem;font-weight:500;transition:all 0.3s ease;cursor:pointer;}\
.btn:hover{background:rgba(255,255,255,0.08);border-color:rgba(255,255,255,0.15);transform:translateY(-2px);}\
.btn:active{transform:translateY(0);}\
.btn span{font-size:1.2rem;}\
.foot{text-align:center;margin-top:1.5rem;color:#333;font-size:0.65rem;letter-spacing:0.5px;}\
.foot a{color:#555;text-decoration:none;}\
.foot a:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
@keyframes pulse{0%,100%{opacity:0.6;}50%{opacity:1;}}\
@keyframes glow{0%,100%{box-shadow:0 0 8px rgba(100,149,237,0.15);}50%{box-shadow:0 0 18px rgba(100,149,237,0.3);}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.glass:nth-child(2){animation-delay:0.1s;}\
.glass:nth-child(3){animation-delay:0.2s;}\
.btn{transition:all 0.3s ease,box-shadow 0.4s ease;}\
.btn:hover{box-shadow:0 0 14px rgba(100,149,237,0.25);}\
</style>\
<body>\
<div id='wrap'>\
<div style='text-align:center;margin-bottom:2rem;'>\
<img src='/favicon.png' alt='Home' style='width:48px;height:48px;border-radius:12px;margin-bottom:1rem;opacity:0.8;'>\
<h1>" INDEX_TITLE "</h1>\
<div class='sub' style='animation:pulse 3s ease-in-out infinite;'>wireless extender</div>\
</div>"
/* Logout button streamed here */

#define INDEX_CHUNK_STATUS_OPEN "\
<div class='glass'>\
<h2>Status</h2>\
<table class='tbl'>"
/* Status rows streamed here */

#define INDEX_CHUNK_STATUS_CLOSE "\
</table>\
</div>"

#if !CONFIG_ETH_UPLINK
#define INDEX_CHUNK_BUTTONS "\
<div class='glass'>\
<h2>Menu</h2>\
<div class='grid'>\
<a href='/setup' class='btn'><span>🚀</span>Setup</a>\
<a href='/scan' class='btn'><span>📡</span>Scan</a>\
<a href='/config' class='btn'><span>⚙️</span>Config</a>\
<a href='/mappings' class='btn'><span>🔀</span>Mappings</a>\
</div></div>"
#else
#define INDEX_CHUNK_BUTTONS "\
<div class='glass'>\
<h2>Menu</h2>\
<div class='grid'>\
<a href='/config' class='btn'><span>⚙️</span>Config</a>\
<a href='/mappings' class='btn'><span>🔀</span>Mappings</a>\
</div></div>"
#endif
/* Auth UI streamed here */

#define INDEX_CHUNK_TAIL "\
<div class='foot'>AeroLink v%s %s %s | <a href='https://github.com/agra-aarav15/AeroLink' target='_blank'>Source</a></div>\
</div></body></html>"
