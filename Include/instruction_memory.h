#ifndef INSTRUCTION_MEMORY_H
#define INSTRUCTION_MEMORY_H

#include <systemc.h>
#include <fstream>

#define INSTR_LEN 16
#define DIR_LEN 4

class Instruction_Memory: public sc_module
{
public:
  sc_in<sc_uint<DIR_LEN>> _Dir_In;
  sc_out<sc_uint<INSTR_LEN>> _Ins_Out;
  sc_out<sc_uint<INSTR_LEN>> _Ins_Out_Next;


  SC_CTOR(Instruction_Memory)
  {
    SC_METHOD(search);
    sensitive << _Dir_In;

    _Mem_File.open("memoryFile.txt");
  }


private:
  std::ifstream _Mem_File;

  void search()
  {
    int dir_From_Pc = _Dir_In.read();
    sc_uint<INSTR_LEN> instruction;
    sc_uint<INSTR_LEN> instruction_next;
    char temp_Instr[INSTR_LEN];

    size_t pos_In_File = dir_From_Pc * (INSTR_LEN+1);
    _Mem_File.seekg(pos_In_File, std::ios::beg);
    _Mem_File.getline(temp_Instr, INSTR_LEN+1);

    for (int i=0; i < INSTR_LEN; ++i)
      if (temp_Instr[i] == '1')
        instruction[INSTR_LEN -1 -i] = 1;
      else
        instruction[INSTR_LEN -1 -i] = 0;

    _Mem_File.getline(temp_Instr, INSTR_LEN+1);
    for (int i=0; i < INSTR_LEN; ++i)
      if (temp_Instr[i] == '1')
        instruction_next[INSTR_LEN -1 -i] = 1;
      else
        instruction_next[INSTR_LEN -1 -i] = 0;

    _Ins_Out.write(instruction);
    _Ins_Out_Next.write(instruction_next);

    std::cout << "instruction: ";
    for (int i=0; i < INSTR_LEN; ++i)
      std::cout  << instruction[INSTR_LEN -1 -i] ;
    std::cout << "\n";
  }

};
#endif // INSTRUCTION_MEMORY_H
