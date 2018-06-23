module main(output[31:0] result,input clk,reset);


wire[2:0] ALUOp;
wire PCSrc,RegDst,ALUSrc,MemToReg,regWrite,MemWrite,MemRead;
wire Zero;
wire[5:0] opcode,func;
control ctrl(ALUOp,PCSrc,RegDst,ALUSrc,MemToReg,regWrite,MemWrite,MemRead,opcode,func,Zero);
datapath mydp(result,opcode,func,Zero,clk,reset,ALUOp,PCSrc,RegDst,ALUSrc,MemToReg,regWrite,MemWrite,MemRead);

endmodule