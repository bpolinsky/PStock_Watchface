<%@ page import="java.io.FileInputStream" %>
<%@ page import="java.io.FileNotFoundException" %>
<%@ page import="java.util.Scanner" %>

<%

Process p = new ProcessBuilder("/cac/u01/mg900/bin/PStock_Watchface/server_side/src/python/query.py", "myarg").start();

p.waitFor();
   
String inputStreamString = new Scanner(p.getInputStream(),"UTF-8").useDelimiter("\\A").next();

out.println(inputStreamString);

//out.println("{ \"Steel\":9 }");
%>
