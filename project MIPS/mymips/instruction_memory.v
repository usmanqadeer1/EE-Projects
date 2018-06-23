module instruction_memory(output reg [31:0] instruction, input[31:0] read_instruct_addr,input clk);
reg[7:0] mem[0:255];
initial begin
	 $readmemb("instruction_list.txt", mem);
			 
			 /* mem[0]=32'b100011_11101_00001_0000000000000000
				mem[4]=32'b100011_11101_00010_0000000000000100
				mem[8]=32'b100011_11101_00011_0000000000001000
				mem[12]=32'b100011_11101_00000_0000000000000000
				mem[16]=32'b100011_11101_00101_0000000000000000
				mem[20]=32'b100011_11101_00110_0000000000001100
				mem[24]=32'b100011_11101_00111_0000000000000000

				mem[28]=32'b000101_00001_00000_0000000001010010
				mem[32]=32'b000000_00010_00011_00100_00000_101011
				mem[36]=32'b000101_00100_00000_0000000000001100
				mem[40]=32'b000101_00011_00000_0000000000100100
				mem[44]=32'b000000_00001_00110_00001_00000_100101
				mem[48]=32'b000010_000000000000000000000111

				mem[52]=32'b000000_00101_00010_00101_00000_100101
				mem[56]=32'b000000_00010_00000_00010_00000_100100
				mem[60]=32'b000000_00010_00011_00010_00000_100101
				mem[64]=32'b000000_00011_00000_00011_00000_100100
				mem[68]=32'b000000_00011_00101_00011_00000_100101
				mem[72]=32'b000010_000000000000000000000111

				mem[76]=32'b000000_00010_00011_00010_00000_100010
				mem[80]=32'b000010_000000000000000000000111

				mem[84]=32'b000000_00111_00010_00111_00000_100101
				mem[88]=32'b101011_11101_00111_0000000000010000
		*/



end

always @(posedge clk) begin
	instruction <={mem[read_instruct_addr],
				   mem[read_instruct_addr+1],
				   mem[read_instruct_addr+2],
				   mem[read_instruct_addr+3]};
end
endmodule
