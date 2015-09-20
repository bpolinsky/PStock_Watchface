<h1>PStock_Watchface</h1>
<strong>Big Red Hacks 2015 Project</strong>
<br/>
PStock_Watchface is a Pebble watchface that displays data change (e.g. daily stock price change) as an emoji. When prompted through an HttpRequest, the server-side code, using a set of current and historical data to determine how drastic a change is, will return a value in the range of 0-10 for each data category being tracked based on how much the value has changed since the last value was recorded and whether then change was in the positive or negative direction. The Pebble watchface then displays an emoji icon that corresponds to this returned value, showing other icons when there is either no data available or there was an error accessing the data.<br/>
<br/>
In the intended use case of tracking stock prices, a value of 10 would mean that the stock price has gone up a very large amount (as determined by previously gathered data) and will result in the following watchface:</br>
<https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/screenshots/10_value.jpg>
<br/>
Whereas a value of 3 would mean that the stock has dropped in price, but it may not have been an extremely large drop. A value of 3 would display:<br/>
<https://raw.githubusercontent.com/bpolinsky/PStock_Watchface/master/stockemoji/3.png>
<br/>
There is also a server-side display that can be seen at: <http://spring.rutgers.edu:8080/pstockwatchface/> that shows not only the entire range of monochrome-emojis but also shows the current color-emojis of data currently available for representation in the Pebble watchface.