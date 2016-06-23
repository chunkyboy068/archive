===================================
Foot Traffic Server and Application
===================================
Thomas Yu
===================================

Overview
----------------------------------------------------------------
Using the foot traffic web server and application, one can track
the amount of traffic at a certain location, as well as the 
environmental conditions at that location.  Data is stored for
a set period of time any taken data can be requested from the
web server.


Android Application
-----------------------------------------------------------------
The android application periodically takes sensor readings (light and
temperature) and a location reading (GPS) and sends it to the web server
on command. For devices that have no temperature sensor, the application
will use the battery temperature sensor by default.

 There are 3 activities which each correspond to a particular
function.  On startup, the first activity will prompt for a web server
ip address/URL and a port number.  Network traffic cannot occur if these
are not set properly.  The second activity is used for sending readings
to the web server.  Once started, sensor readings are scheduled to
be taken automatically.  The readings are shown to the user, providing
live data output. The second activity also allows you to selectively
choose which type of sensor data to display through the use of a dropdown
bar and also to selectively turn off either location or sensor.

When sending data to the web server, there are 3 possible statuses: "staying",
"leaving", or "passing by".  Staying tells the web server to increase the amount of
people at the location by 1 while leaving does the opposite.  "Passing by" does
the same as "staying"but the increase in traffic lasts only for 2 minutes.
A progress bar on the bottom of the screen fills up according to the amount
of sensor readings that have already occurred.  This bar must reach 100% before
the user can actually send data.  25% occurs to a single sensor reading (2 total) 
and 50% corresponds to a GPS location reading.  It is not uncommon to see the bar
"stuck" at 50% since sensor readings are much faster than location updates.  

The third activity allows the user to request data from the web server.  A timepicker
allows for selection of a requested hour over the past 24 hours.  The valid query
consists of a description composed of letters only or comma separated GPS coordinates.
As of v1.0, the description must be a name known by the webserver.  The requested
data is received in JSON format, processed, and shown on the application.  The total
number of people at that location, average temperature for that hour, average light
for that hour, and total foot traffic is displayed.

Both sending and receiving use HttpPost Requests.  See the server documentation for
more information.

Web Server
--------------------------------------------------------------------------------
The webserver uses the Jetty framework.  All data is stored in memory. An hours worth
of data is collected into an HourData object.  24 of these objects (each representing an
hour of the day) are stored into an ArrayList.  This ArrayList corresponds to a single
location.  Multiple Arraylists are stored into a HashMap as <String, ArrayList> pairs.

For more documentation on the web server, please see the web server documentation.

***Please note that there are not many locations already hard coded into the default
server.  The webserver is meant to be edited by adding, new, custom locations before
deployment.  This can be done simply with the function insertNewData(....). Example usage
of this data can be seen in the web server.