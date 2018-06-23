module pc(output reg[31:0] read_instruct_addr, input[31:0] sign_extended,input clk,PCSrc,reset);

	always@(posedge clk)
	begin
	if(reset)	read_instruct_addr<=0;
	else
		begin
		if(PCSrc) read_instruct_addr<=(read_instruct_addr+4)+(sign_extended<<2);
		else read_instruct_addr<=read_instruct_addr+4;
		end

	end
endmodule
	
		
	





