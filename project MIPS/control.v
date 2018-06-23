module control(output reg[2:0] ALUOp,output reg PCSrc,RegDst,ALUSrc,MemToReg,regWrite,MemWrite,MemRead,input[5:0] opcode,func,input Zero);

always @(*)
begin
	if(opcode==6'b000000)	//R-type
	begin
	RegDst<=1; regWrite<=1; ALUSrc<=0; MemWrite<=0; MemRead<=0; MemToReg<=0; PCSrc<=0;
	
		case (func)
			6'b100100 :	 ALUOp<=0; 		//and
			6'b100101 :  ALUOp<=1; 		//or
			6'b100000 :  ALUOp<=2; 		//add
			6'b100010 :  ALUOp<=3;		//sub	
			6'b100110 :  ALUOp<=4; 		//xor
			6'b101011 :  ALUOp<=5;		//sltu
			6'b101010 :  ALUOp<=6; 		//slt
			default   :  ALUOp<=7; 		//nothing
		endcase
	end
	else if(opcode==6'b100011)			  begin ALUOp<=2; RegDst<=0    ;regWrite<=1 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=1 ;MemToReg<=1   ; PCSrc<=0;end	//lw
	else if(opcode==6'b101011)			  begin ALUOp<=2; RegDst<=1'bx ;regWrite<=0 ;ALUSrc<=1 ;MemWrite<=1 ;MemRead<=0 ;MemToReg<=1'bx; PCSrc<=0;end	//sw
	else if(opcode==6'b000100 ) begin
									ALUOp<=3;if(Zero==1)begin RegDst<=1'bx ;regWrite<=0 ;ALUSrc<=0 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=1'bx; PCSrc<=1;end
											 else		begin RegDst<=1'bx ;regWrite<=0 ;ALUSrc<=0 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=1'bx; PCSrc<=0;end
								end	//beq
	else if(opcode==6'b000101 ) begin
									ALUOp<=3;if(Zero!=1) begin RegDst<=1'bx ;regWrite<=0 ;ALUSrc<=0 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=1'bx; PCSrc<=1;end
											else 		 begin RegDst<=1'bx ;regWrite<=0 ;ALUSrc<=0 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=1'bx; PCSrc<=0;end
								end	//bneq
	else if(opcode==6'b001100)			  begin ALUOp<=0; RegDst<=0	   ;regWrite<=1 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=0   ; PCSrc<=0;end 	//andi
	else if(opcode==6'b001101) 			  begin ALUOp<=1; RegDst<=0    ;regWrite<=1 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=0   ; PCSrc<=0;end 	//ori
	else if(opcode==6'b001000)			  begin ALUOp<=2; RegDst<=0    ;regWrite<=1 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=0   ; PCSrc<=0;end 	//addi
	else if(opcode==6'b001010)			  begin ALUOp<=6; RegDst<=0    ;regWrite<=1 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=0   ; PCSrc<=0;end 	//slti
	
	else if(opcode==6'b000010) begin ALUOp<=7; RegDst<=1'bx; regWrite<=0 ;ALUSrc<=1 ;MemWrite<=0 ;MemRead<=0 ;MemToReg<=0; PCSrc<=1;end	//jump---J-type
	
end
endmodule