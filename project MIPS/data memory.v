module data_memory (output  [31:0] read_data, input [31:0] read_addr,write_addr, write_data,input memwrite, memread,clk);

reg [31:0] MEMO[0:255];  

integer i;

initial begin
 /* read_data <= 0;*/

  $readmemh("data_list.txt",MEMO);
  
 /* MEMO[0]=32'h0;
  MEMO[1]=32'h20;
  
  MEMO[2]=32'h30;
  MEMO[3]=32'h0;
  
  for(i=4;i<256;i=i+1)
	MEMO[i]=i;*/

end

assign read_data =(memread)? MEMO[read_addr]:read_data;

always @(posedge clk) begin
  if (memwrite == 1'b1) begin
    MEMO[write_addr] <= write_data;
  end

 /*else if (memread == 1'b1) begin
    read_data <= MEMO[read_addr];
  end*/
end

endmodule