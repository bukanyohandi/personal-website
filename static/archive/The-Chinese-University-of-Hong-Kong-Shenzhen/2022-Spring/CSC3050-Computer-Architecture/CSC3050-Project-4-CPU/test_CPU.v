`timescale 1ns / 1ps
`include "CPU.v"

module test_CPU;

reg clock, start, init;
integer fd, idx;

CPU run(.clock(clock), .start(start));

initial 
    begin
        clock = 0;
        start = 0;
        init = 1;
        
        $display("\n\nDisplaying the PC and first seven registers...\n\n");
        $display("   PC   |   at   |   v0   |   v1   |   a0   |   a1   |   a2   |   a3");

        while(run.ongoing == 1'b1 || init == 1)
            begin
                #10 $display("%h|%h|%h|%h|%h|%h|%h|%h", run.PC, run.register[1], run.register[2], run.register[3], run.register[4], run.register[5], run.register[6], run.register[7]);
                init = 0;
            end

        // To make sure the last instruction finished the 5th stage. 
        #10
        #10
        #10
        #10
        #10

        $display("   PC   |   at   |   v0   |   v1   |   a0   |   a1   |   a2   |   a3");

        $display("\n\nPlease find the DATA_RAM.txt file in the same folder :)\n\n");

        fd = $fopen("DATA_RAM.txt", "w");
        for(idx = 0; idx < 512; idx++)
            begin
                $fdisplay(fd, "%b", run.MainMemory_CPU.DATA_RAM[idx]);
            end
        $fclose(fd);

        #10 $finish;
    end

always #5 clock = ~clock;

endmodule

