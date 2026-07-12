/* Firewall page templates */
/* Firewall Page - Chunked for streaming */
#define FIREWALL_CHUNK_HEAD "<html>\
<head>\
<meta name='viewport' content='width=device-width, initial-scale=1, maximum-scale=1, user-scalable=0'>\
<meta charset='UTF-8'>\
<title>AeroLink — Firewall</title>\
<link rel='icon' href='favicon.png'>\
<link href='https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700&display=swap' rel='stylesheet'>\
</head>\
<style>\
*{box-sizing:border-box;margin:0;padding:0;}\
body{font-family:'Inter',sans-serif;background:#000;color:#fff;padding:1.5rem;min-height:100vh;display:flex;justify-content:center;}\
#wrap{width:100%;max-width:800px;}\
h1{font-size:1.1rem;font-weight:300;color:#fff;letter-spacing:3px;text-transform:uppercase;margin-bottom:0.3rem;}\
h2{font-size:0.7rem;font-weight:600;color:#555;text-transform:uppercase;letter-spacing:2px;margin:1.2rem 0 0.6rem;border-bottom:1px solid rgba(255,255,255,0.05);padding-bottom:0.4rem;}\
h3{font-size:0.7rem;font-weight:600;color:#666;margin:0.6rem 0 0.3rem;}\
.glass{background:rgba(255,255,255,0.04);backdrop-filter:blur(20px);-webkit-backdrop-filter:blur(20px);border:1px solid rgba(255,255,255,0.08);border-radius:16px;padding:1.2rem;margin-bottom:1rem;}\
a.home{display:inline-flex;align-items:center;gap:0.5rem;color:#555;text-decoration:none;font-size:0.75rem;margin-bottom:1.2rem;transition:color 0.3s;}\
a.home:hover{color:#aaa;}\
@keyframes fadeIn{from{opacity:0;transform:translateY(12px);}to{opacity:1;transform:translateY(0);}}\
.glass{animation:fadeIn 0.5s ease-out both;}\
.glass:nth-child(2){animation-delay:0.08s;}\
.acl{animation:fadeIn 0.4s ease-out both;}\
.ok-btn{transition:all 0.3s ease,box-shadow 0.3s;}\
.ok-btn:hover{box-shadow:0 0 10px rgba(100,149,237,0.2);}\
.tbl{width:100%%;border-collapse:collapse;font-size:0.7rem;}\
.tbl th{font-size:0.6rem;font-weight:600;color:#444;text-transform:uppercase;letter-spacing:1px;text-align:left;padding:0.4rem;border-bottom:1px solid rgba(255,255,255,0.06);}\
.tbl td{padding:0.4rem;border-bottom:1px solid rgba(255,255,255,0.03);color:#aaa;}\
.ftbl{width:100%%;border-collapse:collapse;}\
.ftbl td{padding:0.3rem 0;vertical-align:top;}\
.ftbl td:first-child{color:#444;font-size:0.7rem;padding-right:0.5rem;width:20%%;text-align:right;text-transform:uppercase;}\
input[type='text'],input[type='number'],select{width:100%%;max-width:100%;background:rgba(255,255,255,0.04);border:1px solid rgba(255,255,255,0.08);border-radius:6px;color:#fff;padding:0.4rem;font-size:0.8rem;box-sizing:border-box;overflow:hidden;}\
input:focus,select:focus{outline:none;border-color:rgba(255,255,255,0.2);}\
.ok-btn{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:6px;padding:0.4rem 0.8rem;font-size:0.8rem;cursor:pointer;width:100%%;margin-top:0.2rem;}\
.ok-btn:hover{background:rgba(255,255,255,0.14);}\
.rbtn{background:rgba(255,255,255,0.05);color:#aaa;border:1px solid rgba(255,255,255,0.06);border-radius:4px;padding:0.2rem 0.4rem;font-size:0.65rem;cursor:pointer;}\
.obtn{background:rgba(255,152,0,0.1);color:#ff9800;border:1px solid rgba(255,152,0,0.15);border-radius:4px;padding:0.2rem 0.4rem;font-size:0.65rem;cursor:pointer;}\
.acl{margin-bottom:0.8rem;padding:0.6rem;background:rgba(255,255,255,0.02);border:1px solid rgba(255,255,255,0.04);border-radius:10px;}\
.stats{font-size:0.65rem;color:#444;margin-bottom:0.3rem;}\
.stats .ok{color:#4caf50;}\
.stats .no{color:#f44336;}\
.modal{display:none;position:fixed;top:0;left:0;width:100%%;height:100%%;background:rgba(0,0,0,0.8);z-index:1000;justify-content:center;align-items:center;backdrop-filter:blur(5px);}\
.modal.show{display:flex;}\
.mbox{background:#111;border:1px solid rgba(244,67,54,0.3);border-radius:12px;padding:1.5rem;max-width:350px;text-align:center;}\
.mbox h3{color:#f44336;margin-bottom:0.8rem;}\
.mbox p{color:#888;margin-bottom:1rem;font-size:0.85rem;}\
.mbox button{background:rgba(255,255,255,0.08);color:#fff;border:1px solid rgba(255,255,255,0.1);border-radius:8px;padding:0.5rem 1.5rem;cursor:pointer;}\
@media(max-width:768px){body{padding:1rem;}.tbl{display:block;overflow-x:auto;}.tbl th,.tbl td{padding:0.3rem 0.2rem;font-size:0.6rem;}}\
</style>\
<body>"
#define FIREWALL_CHUNK_MID1 "\
<div id='wrap'>\
<a href='/' class='home'>← Home</a>\
<h1>AeroLink — Firewall</h1>"
#define FIREWALL_CHUNK_MID2 "\
<p style='color:#333;font-size:0.7rem;margin-bottom:0.6rem;'>Rules top-down. First match wins.</p>"
#define FIREWALL_CHUNK_TAIL "\
<div class='glass'>\
<h2>Add Rule</h2>\
<form action='/firewall' method='GET'>\
<table class='ftbl'>\
<tr><td>Dir</td><td><select name='acl_list'><option value='0'>To ESP</option><option value='1'>From ESP</option><option value='2'>To AP</option><option value='3'>From AP</option></select></td></tr>\
<tr><td>Proto</td><td><select name='proto'><option value='0'>IP</option><option value='6'>TCP</option><option value='17'>UDP</option><option value='1'>ICMP</option></select></td></tr>\
<tr><td>SRC IP</td><td><input type='text' name='src_ip' placeholder='any'/></td></tr>\
<tr><td>SRC Port</td><td><input type='text' name='src_port' placeholder='*'/></td></tr>\
<tr><td>DST IP</td><td><input type='text' name='dst_ip' placeholder='any'/></td></tr>\
<tr><td>DST Port</td><td><input type='text' name='dst_port' placeholder='*'/></td></tr>\
<tr><td>Action</td><td><select name='action'><option value='1'>Allow</option><option value='0'>Deny</option><option value='3'>Allow+Mon</option><option value='2'>Deny+Mon</option></select></td></tr>\
<tr><td></td><td><input type='submit' name='acl_action' value='Add' class='ok-btn'/></td></tr>\
</table></form></div>\
</div></body></html>"
