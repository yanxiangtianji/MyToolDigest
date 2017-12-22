# MyToolDigest

Digestion of interesting and reusable templates and functions from my previous works.

## - CppMySQLBinding (C++)

A C++ style template binding of MySQL database.

## - power_law_distribution (C++)

A STL style distribution for power law.

## - my_type_traits (C++)

Some additional type_traits for meta-programming like is_contailer, is_pair.

## - streaming_container (C++)

Adapt many STL types to ostream.
Used for logging, debugging and unit testing.

## - Bunch Experiment (shell + Python)

### - Task Launch

1. timed-task.sh

    Run a task with a timeout. Filed tasks will be put into a record file and/or a specific note.

### - Result Analysis

1. make-table.py

    Make several serialized multiple lists into a table. Each different list is separated by a line starting with "x".

1. avg-table.py and merge-table.sh

    Summarize several tables into one table. The mean value of a row in a table is used as its summarized value in the new table.

## - Multiple Launcher (C++)

A system used to launch a program at multiple instances (multiple thread and/or multiple machines).
It is similiar to functionality of mpirun from the MPI system.

Supports:

1. multiple processes + multiple machines
1. parameter forwarding
1. slot file (machine address, number of slot on each machine)

Depends: Boost.Asio.

## - Message Driver (C++)

A general message driver together with some convirence tools like Synchronization-Unit, Conditional-Launcher.
Callback fucntion type: `void(const std::string&, const RPCInfo&)`.
The first parameter is the input parameter, and the second is a struct of {source, destination, type}.

Example: handling RPC request from network.

## - Zlog (C++) (To be done)

A light weight STL liked logging system without 3rd party dependency.

Supports:
```c++
// 1. normal output
zout<<a<<b;
// 2. verbose output, actually showd when global verbos option level is higher or euqal to it
zout(lvl)<<a<<b;
// 3. conditional output
zout_if(cond)<<a<<b;
// 4. verbose conditional output
zout_if(cond,lvl)<<a<<b;
```
