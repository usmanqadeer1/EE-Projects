module regfile( output [31:0] rdData1, output [31:0] rdData2,input clk,reset,regWrite,input[31:0] wrData,input[4:0] rdAddr1, rdAddr2, wrAddr);

   reg [31:0] register [0:31];

   assign rdData1 = register[rdAddr1];
   assign rdData2 = register[rdAddr2];

   integer 	 i;
   always @(posedge clk) begin
      if (reset) begin
		for (i = 0; i < 32; i = i + 1) begin
	    register[i] <= 0;
		end
      end 
	  
	  else begin
	    if (regWrite) register[wrAddr] <= wrData;
      end 
   end
endmodule