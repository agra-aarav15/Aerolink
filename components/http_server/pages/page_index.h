/* Index page templates */
#include "router_config.h"

#if CONFIG_ETH_UPLINK
#define INDEX_TITLE "AeroLink (LAN)"
#else
#define INDEX_TITLE "AeroLink"
#endif

/* Index Page - Chunked for streaming.
 * Shared design language for the whole dashboard:
 * pure-black canvas, frosted glass cards, hairline borders,
 * one electric-blue accent, no visual noise. */
#define INDEX_CHUNK_HEAD "<!doctype html>\
<html lang='en'>\
<head>\
<meta charset='utf-8'>\
<meta name='viewport' content='width=device-width,initial-scale=1'>\
<meta name='color-scheme' content='dark'>\
<meta name='theme-color' content='#000000'>\
<title>" INDEX_TITLE "</title>\
<link rel='icon' href='/favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600;700&display=swap' rel='stylesheet'>\
<style>\
*{box-sizing:border-box;margin:0;padding:0}\
html{-webkit-text-size-adjust:100%}\
body{font-family:'Inter',system-ui,-apple-system,'Segoe UI',Roboto,Helvetica,Arial,sans-serif;background:#000;color:#eef1f6;color-scheme:dark;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding:1.2rem 1rem calc(1.6rem + env(safe-area-inset-bottom))}\
body::before{content:'';position:fixed;inset:0;z-index:0;pointer-events:none;background:radial-gradient(700px 340px at 50% -120px,rgba(79,140,255,.22),transparent 70%),radial-gradient(520px 420px at 110% 110%,rgba(79,140,255,.07),transparent 70%)}\
#wrap{position:relative;z-index:1;width:100%;max-width:540px;margin:auto}\
a{color:#7fa9ff;text-decoration:none}\
a:hover{color:#aecbff}\
:focus-visible{outline:2px solid rgba(127,169,255,.8);outline-offset:2px}\
::selection{background:rgba(79,140,255,.35)}\
.hero{text-align:center;margin-bottom:1.7rem}\
:root{--logo:url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 64 64'%3E%3Crect width='64' height='64' rx='15' fill='%23070b14'/%3E%3Cpath d='M18 47 32 17 46 47' fill='none' stroke='%234f8cff' stroke-width='6.5' stroke-linecap='round' stroke-linejoin='round'/%3E%3Cpath d='M24.5 37.5h15' stroke='%234f8cff' stroke-width='6.5' stroke-linecap='round'/%3E%3C/svg%3E\")}\
.logo{display:block;width:54px;height:54px;border-radius:15px;margin:0 auto .9rem;background:#070b14 var(--logo) center/62% no-repeat;box-shadow:0 0 0 1px rgba(255,255,255,.14),0 12px 34px rgba(0,0,0,.65);overflow:hidden}\
.logo img{display:block;width:100%;height:100%;object-fit:contain}\
.hero h1{font-size:1.05rem;font-weight:600;letter-spacing:.34em;text-transform:uppercase;margin-left:.34em}\
.hero .sub{margin-top:.5rem;color:#7f8794;font-size:.68rem;letter-spacing:.22em;text-transform:uppercase}\
h2{font-size:.68rem;font-weight:600;letter-spacing:.16em;text-transform:uppercase;color:#8b93a1;margin-bottom:.85rem}\
.glass{background:linear-gradient(165deg,rgba(255,255,255,.055),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.09);border-radius:18px;padding:1.2rem 1.2rem 1.3rem;backdrop-filter:blur(18px) saturate(150%);-webkit-backdrop-filter:blur(18px) saturate(150%);box-shadow:0 12px 40px rgba(0,0,0,.5),inset 0 1px 0 rgba(255,255,255,.05);margin-bottom:1rem;animation:rise .5s cubic-bezier(.2,.7,.3,1) both}\
@keyframes rise{from{opacity:0;transform:translateY(14px)}to{opacity:1;transform:none}}\
@keyframes pop{from{opacity:0;transform:scale(.94)}to{opacity:1;transform:none}}\
@keyframes pulse{0%,100%{opacity:.5}50%{opacity:1}}\
@keyframes spin{to{transform:rotate(360deg)}}\
table{width:100%;border-collapse:collapse}\
.tbl{width:100%;border-collapse:collapse}\
.tbl td{padding:.62rem .3rem;font-size:.84rem;color:#cfd5de;border-bottom:1px solid rgba(255,255,255,.05);vertical-align:middle}\
.tbl tr:last-child td{border-bottom:none}\
.tbl td:first-child{color:#8b93a1;font-size:.68rem;letter-spacing:.1em;text-transform:uppercase;text-align:right;padding-right:1rem;width:44%;white-space:nowrap}\
.tbl td:last-child{color:#eef1f6}\
.tbl td strong{color:#fff;font-weight:600}\
.grid{display:grid;grid-template-columns:1fr 1fr;gap:.7rem;margin-top:.2rem}\
.btn{display:flex;flex-direction:column;align-items:center;justify-content:center;gap:.55rem;min-height:90px;padding:1rem .6rem;background:linear-gradient(165deg,rgba(255,255,255,.05),rgba(255,255,255,.018));border:1px solid rgba(255,255,255,.08);border-radius:14px;color:#e7ecf5;font-size:.8rem;font-weight:500;letter-spacing:.05em;text-align:center;transition:transform .18s,border-color .18s,box-shadow .18s,background .18s}\
.btn span{font-size:1.5rem;line-height:1;filter:grayscale(1) brightness(1.75);opacity:.9;transition:filter .2s,opacity .2s}\
.btn:hover{transform:translateY(-3px);color:#fff;border-color:rgba(127,169,255,.5);background:linear-gradient(165deg,rgba(79,140,255,.16),rgba(79,140,255,.05));box-shadow:0 14px 30px rgba(0,0,0,.5),0 0 0 1px rgba(127,169,255,.25)}\
.btn:hover span{filter:none;opacity:1}\
.btn:active{transform:translateY(-1px)}\
.btn:last-child:nth-child(odd){grid-column:1/-1}\
a[href*='logout']{position:absolute!important;top:.1rem;right:0;padding:.45rem .95rem!important;border-radius:999px!important;background:rgba(255,255,255,.05)!important;border:1px solid rgba(255,255,255,.14)!important;color:#c4cad3!important;font-size:.68rem!important;font-weight:600!important;font-family:inherit!important;letter-spacing:.12em;text-transform:uppercase;text-decoration:none!important;transition:all .18s!important}\
a[href*='logout']:hover{color:#fff!important;background:rgba(255,84,84,.14)!important;border-color:rgba(255,120,120,.5)!important}\
input[name='login_password'],input[name='new_password'],input[name='confirm_password']{width:100%!important;padding:.68rem .75rem!important;margin:0 0 .6rem!important;background:rgba(255,255,255,.05)!important;border:1px solid rgba(255,255,255,.12)!important;border-radius:10px!important;color:#fff!important;font-size:.9rem!important;font-family:inherit!important;box-sizing:border-box!important;transition:border-color .18s,box-shadow .18s!important}\
input[name='login_password']:focus,input[name='new_password']:focus,input[name='confirm_password']:focus{outline:none!important;border-color:rgba(79,140,255,.7)!important;box-shadow:0 0 0 3px rgba(79,140,255,.2)!important}\
input[name='login_password']::placeholder,input[name='new_password']::placeholder,input[name='confirm_password']::placeholder{color:#5b6270!important}\
input[type='submit'][value='Login'],input[type='submit'][value='Set Password'],input[type='submit'][value='Change Password']{width:100%!important;padding:.7rem!important;margin:0!important;background:linear-gradient(180deg,#4f8cff,#3b74de)!important;border:1px solid rgba(79,140,255,.55)!important;border-radius:10px!important;color:#fff!important;font-size:.88rem!important;font-weight:600!important;font-family:inherit!important;letter-spacing:.04em;cursor:pointer!important;box-shadow:0 6px 18px rgba(59,116,222,.3)!important;transition:filter .15s!important}\
input[type='submit'][value='Login']:hover,input[type='submit'][value='Set Password']:hover,input[type='submit'][value='Change Password']:hover{filter:brightness(1.1)!important}\
.notice{margin-top:1rem;padding:.8rem .9rem;border-radius:12px;font-size:.78rem;line-height:1.5}\
.foot{text-align:center;margin-top:1.5rem;color:#565d68;font-size:.66rem;letter-spacing:.06em}\
.foot b{color:#98a1ae;font-weight:600}\
.foot a{color:#7d8694;border-bottom:1px solid rgba(255,255,255,.18);padding-bottom:1px}\
.foot a:hover{color:#a9c8ff;border-color:rgba(127,169,255,.6)}\
@media(max-width:560px){\
body{padding:.9rem .75rem calc(1.2rem + env(safe-area-inset-bottom))}\
.glass{padding:1rem .95rem 1.05rem;border-radius:16px}\
.hero{margin-bottom:1.3rem}\
.btn{min-height:80px;font-size:.76rem}\
.tbl td:first-child{padding-right:.6rem}\
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
<div class='hero'>\
<span class='logo'><img src='/favicon.png' alt=''></span>\
<h1>" INDEX_TITLE "</h1>\
<div class='sub'>wireless extender console</div>\
</div>"
/* Logout button streamed here (pinned top-right via a[href*=logout] rule) */

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
<a href='/firewall' class='btn'><span>🛡️</span>Firewall</a>\
</div></div>"
#else
#define INDEX_CHUNK_BUTTONS "\
<div class='glass'>\
<h2>Menu</h2>\
<div class='grid'>\
<a href='/config' class='btn'><span>⚙️</span>Config</a>\
<a href='/mappings' class='btn'><span>🔀</span>Mappings</a>\
<a href='/firewall' class='btn'><span>🛡️</span>Firewall</a>\
</div></div>"
#endif
/* Auth UI streamed here */

#define INDEX_CHUNK_TAIL "\
<div class='foot'>AeroLink <b>v%s</b> &middot; %s %s &middot; <a href='https://github.com/agra-aarav15/AeroLink' target='_blank' rel='noopener'>Source</a></div>\
</div></body></html>"
