module ALU(output reg[31:0] out,output reg Zero ,input[31:0] a,b, input[2:0] ALUOp);
always @(*)
begin
	case(ALUOp)
	0:	out <= a & b;			//and
	1:	out <= a | b;			//or
	2:	out <= a + b;			//add
	3:	out <= a - b;			//sub
	4:  out <= a ^ b;			//xor
	5:  out <= a < b;			//sltu
	6: begin					//slt
			if(a[31] != b[31])
				begin
				if(a[31] > b[31])  out<=1;
				else 			   out<=0;
				end
			else 
				begin
				if(a<b) out<=1;
				else 	out<=0;
				end
				
		end
	endcase
end

always @(out) begin
		if (out == 0)
			Zero <= 1;
		else
			Zero <= 0;
	end
endmodule