module regfile( output reg [15:0] rdData1, output reg [15:0] rdData2,input clk,regWrite,input [15:0] wrData,input [3:0] rdAddr1, rdAddr2, wrAddr);

reg [31:0] register [0:15];

   always @(*) begin
      case (rdAddr1)
	0 : rdData1 = register[0];
	1 : rdData1 = register[1];
	2 : rdData1 = register[2];
	3 : rdData1 = register[3];
	4 : rdData1 = register[4];
	5 : rdData1 = register[5];
	6 : rdData1 = register[6];
	7 : rdData1 = register[7];
	8 : rdData1 = register[8];
	9 : rdData1 = register[9];
	10: rdData1 = register[10];
	11: rdData1 = register[11];
	12: rdData1 = register[12];
	13: rdData1 = register[13];
	14: rdData1 = register[14];
	15: rdData1 = register[15];
	default: rdData1 = 16'hXXXX;
      endcase
   end
   
   always @(*) begin
      case (rdAddr2)
	0 : rdData2 = register[0];
	1 : rdData2 = register[1];
	2 : rdData2 = register[2];
	3 : rdData2 = register[3];
	4 : rdData2 = register[4];
	5 : rdData2 = register[5];
	6 : rdData2 = register[6];
	7 : rdData2 = register[7];
	8 : rdData2 = register[8];
	9 : rdData2 = register[9];
	10: rdData2 = register[10];
	11: rdData2 = register[11];
	12: rdData2 = register[12];
	13: rdData2 = register[13];
	14: rdData2 = register[14];
	15: rdData2 = register[15];
	default: rdData2 = 16'hXXXX;
      endcase
   end
   always @(posedge clk) begin
      if (regWrite) 
	case (wrAddr) 
	  0 : register[0]  <= wrData;
	  1 : register[1]  <= wrData;
	  2 : register[2]  <= wrData;
	  3 : register[3]  <= wrData;
	  4 : register[4]  <= wrData;
	  5 : register[5]  <= wrData;
	  6 : register[6]  <= wrData;
	  7 : register[7]  <= wrData;
      8 : register[8]  <= wrData;
	  9 : register[9]  <= wrData;
	  10: register[10] <= wrData;
	  11: register[11] <= wrData;
	  12: register[12] <= wrData;
	  13: register[13] <= wrData;
	  14: register[14] <= wrData;
	  15: register[15] <= wrData;
	endcase 
   end 
endmodule