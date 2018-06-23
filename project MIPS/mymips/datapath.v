module datapath(output[31:0] result,output Zero,input clk,reset,input[2:0] ALUOp,input PCSrc,RegDst,ALUSrc,MemToReg,
				input regWrite,MemWrite,MemRead);

wire[31:0] rdData1,rdData2,wrData;
wire[31:0] instruction,sign_extended;
wire[31:0] alu_in1,alu_in2;
wire[31:0] read_d_data,write_d_data,read_d_addr,write_d_addr;
wire[31:0] read_instruct_addr;
wire[4:0] write_register_addr;


signextension ss(sign_extended,instruction[15:0]);
pc mypc(read_instruct_addr,sign_extended,clk,PCSrc,reset);
instruction_memory myIM(instruction,read_instruct_addr,clk);
mux m1(write_register_addr,instruction[20:16],instruction[15:11],RegDst);
regfile myregfile( rdData1,rdData2,clk,reset,regWrite,wrData,instruction[25:21], instruction[20:16], write_register_addr);
mux31 m2(alu_in2,rdData2,sign_extended,ALUSrc);
assign alu_in1=rdData1;
ALU myalu(result,Zero ,alu_in1,alu_in2,ALUOp);
assign read_d_addr=result;
assign write_d_addr=result;
assign write_d_data=rdData2;
data_memory mydata(read_d_data,read_d_addr,write_d_addr, write_d_data,MemWrite, MemRead,clk);
mux31 m3(wrData,result,read_d_data,MemToReg);

endmodule


module mux(output[4:0] out,input[4:0] in1,in2,input sel);
assign out=sel?in2:in1;
endmodule

module mux31(output[31:0] out,input[31:0] in1,in2,input sel);
assign out=sel?in2:in1;
endmodule

module signextension(output[31:0] sign_extended,input[15:0] not_extended);
assign sign_extended[15:0]=not_extended[15:0];
assign sign_extended[31:16]=not_extended[15];
endmodule
