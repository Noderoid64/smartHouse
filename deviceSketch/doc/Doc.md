Udp message structure:

\<ip\>/\<command\>/\<data>

ip - sender ip <br>
command:<br>
0 - ask for ping<br>
1 - respond for ping<br>
2 - ask for details<br>
3 - respond for details with data in format \<mac>/\<type>/\<version><br>
data - devided by "/"