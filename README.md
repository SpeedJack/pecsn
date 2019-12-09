# pecsn
Performance Evaluation of Computer Systems and Networks - PROJECT

## Project 14 - Epidemic broadcast (2)
Consider a 2D floorplan with _N_ users randomly dropped in it. A random user
within the floorplan produces a _message_, which should ideally reach all the
users as soon as possible. Communications are _slotted_, meaning that on each
slot a user may or may not relay the message, and a message occupies an entire
slot. A _broadcast radius R_ is defined, so that every receiver who is within a
radius _R_ from the transmitter will receive the message, and no other user
will hear it. A user that receives more than one message in the same slot will
not be able to decode it (_collision_).

Users relay the message they receive _once_, according to the following policy
(_trickle relaying_): after the user successfully receives a message, it waits
for a time window of _T_ slots. If during that time window it correctly
receives less than _m_ copies of the same message, it relays it, otherwise it
stops.

A sender does not know (or cares about) whether or not its message has been
received by its neighbors.

Measure at least the broadcast time for a message in the entire floorplan, the
percentage of covered users, the number of collisions.

In all cases, it is up to the team to calibrate the scenarios so that
meaningful results are obtained.

Project deliverables:
 - Documentation (according to the standards set during the lectures)
 - Simulator code
 - Presentation (up to 10 slides maximum)
