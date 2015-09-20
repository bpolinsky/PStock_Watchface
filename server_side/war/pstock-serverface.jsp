<%@ page import="java.io.FileInputStream" %>
<%@ page import="java.io.FileNotFoundException" %>
<%@ page import="java.util.Scanner" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="java.util.Iterator" %>

<%
Process p = new ProcessBuilder("/cac/u01/mg900/bin/PStock_Watchface/server_side/src/python/query.py", "myarg").start();
p.waitFor();
String inputStreamString = new Scanner(p.getInputStream(),"UTF-8").useDelimiter("\\A").next();
out.println(inputStreamString);
/*
   String t = "{'phonetype':'95','cat':'WP'}";

   HashMap<String, String> map = new HashMap<String, String>();
   JSONObject jObject = new JSONObject(t);
   Iterator<?> keys = jObject.keys();
   
   while( keys.hasNext() ){
   String key = (String)keys.next();
   String value = jObject.getString(key); 
   map.put(key, value);
   }
   
   System.out.println("json : "+jObject);
   System.out.println("map : "+map);

*/

%>

<!DOCTYPE HTML>
<HTML>
  <head>
    <link href='https://fonts.googleapis.com/css?family=Wire+One' rel='stylesheet' type='text/css'>
    <link rel="stylesheet" type="text/css" href="pstock-serverface.css">
  </head>
  <body>
    <h1>The Faces of PStock</h1>

    <div class="middleResults">
<%
%>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/stockemoji-color/<% out.println(); %>c.png" style="width:12%"/>
    </div>

    <div class="footer">
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/closed.png" style="width:7%"/>
      
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/0.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/1.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/2.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/3.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/4.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/5.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/6.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/7.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/8.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/9.png" class="bottomimg"/>
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/10.png" class="bottomimg"/> 
      
      <img src="https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/error.png" style="width:6%"/>
    </div>
  </body>
</HTML>
