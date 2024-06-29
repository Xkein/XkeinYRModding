#pragma once

class IEdGraphCompilerBackend;
class EdGraph;

struct EdGraphCompilerContext
{
    IEdGraphCompilerBackend* compiler;
    EdGraph*                 graph;


};

class IEdGraphCompilerBackend
{

};

 class EdGraphCompilerVMBackend : IEdGraphCompilerBackend
 {
 public:

 };

class EdGraphCompilerJsBackend : public IEdGraphCompilerBackend
{

};

