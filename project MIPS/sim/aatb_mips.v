module aatb_mips;

reg clk,reset;
wire[15:0] myout;

main my(myout,clk,reset);

initial begin
clk=0;
forever #1 clk=~clk;
end


initial begin
reset=1;
#10
reset=0;
#500

$stop;
end
endmodule
