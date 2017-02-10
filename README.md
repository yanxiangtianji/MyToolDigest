# MyToolDigest

Digestion of interesting and reusable templates and functions from my previous works.

## - CppMySQLBinding

A C++ style template binding of MySQL database.

## - power_law_distribution

A STL style distribution for power law.

## - my_type_traits

Some additional type_traits for meta-programming like is_contailer, is_pair.

## - streaming_container

Adapt many STL types to ostream.
Used for logging, debugging and unit testing.

## - Zlog

A light weight STL liked logging system without 3rd party dependency.

Supports:

1. zout<<a<<b;              // normal output
1. zout(lvl)<<a<<b;         // verbos output, actually showd when global verbos option level is higher or euqal to it
1. zout_if(cond)<<a<<b;     // conditional output
1. zout_if(cond,lvl)<<a<<b; // verbos conditional output

## - Multiple Launcher

A system used to launch a program at multiple instances (multiple thread and/or multiple machines).
It is similiar to functionality of mpirun from the MPI system.

Supports:

1. multiple processes + multiple machines
1. parameter forwarding
1. slot file (machine address, number of slot on each machine)

Depends: Boost.Asio.

## - Message Driver

A general message driver together with some convirence tools like Synchronization-Unit, Conditional-Launcher.
Callback fucntion type: `void(const std::string&, const RPCInfo&)`.
The first parameter is the input parameter, and the second is a struct of {source, destination, type}.

Example: handling RPC request from network.

