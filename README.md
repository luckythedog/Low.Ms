Low.Ms
======

Low.Ms will allow developers to use a Cloud linking system (in combination with a C10k solution) in order to develop more easily for massive-scale projects.

Cloud Linking
======

Low.Ms uses a system where Clouds can be ran on different machines. It is recommended to keep Clouds in a Local Area Network rather than on a Wide Area Network (although it is still possible).

There are three types of Clouds: Heavy, Light, and Data.

Heavy Clouds prioritizes in tracking clients and rerouting them to their list of Light Clouds. Being that they provide access to the Light Clouds, they are able to keep a directory of where clients are. Heavy Clouds will use a request ticket system much like DMV in order to handle synchronization between Light Cloud servers.

Light Clouds accept clients that are passed on to them by Heavy Clouds. They handle a certain amount of clients using a C10k solution. Using the Heavy Cloud's directory, Light Clouds can find clients that are not on their list and establish a direct communication with the Light Cloud that it is on.

Data Clouds are assigned a Database and a specified range (like A-C, 1-3, or A-Z). Data Clouds memcache recently used data and flushes it to the Database at a certain interval. This allows Low.Ms to get away from the typical speeds you see with Database queries.

Events and Scripting
======

Platforms
======
