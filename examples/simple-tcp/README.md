# simple-tcp, a TCP client for the concluster library

This client creates X number of server and sender nodes that perform a one-to-one communication event - each sender requests that a server shut down before exiting themselves. An atomic counter is incremented following a successful send event, the result of this counter is outputted at the end of the program execution. It *should* equal the inputted argument that the user gave.

To do this, a cluster is created with X nodes, each node has a serve function associated with it, and an action function.

To undertake the chatter event, the server of each node is invoked, and then shortly after the action function (the sender) is invoked. The action of each node sends a shut off request to a different node.
