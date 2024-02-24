`timescale 1ns / 1ps
`include "InstructionRAM.v"
`include "MainMemory.v"


module CPU(clock, start);
    // Input
    input wire clock, start;

    // Registers
    reg [31:0] register[31:0];
    reg [31:0] PC = 32'h0000_0000;

    // Variables
    reg jump, branch, ongoing;
    reg [5:0] opcode, func;
    reg [31:0] register_A, register_B, register_C, address, jump_address, branch_address, ra;
    wire [31:0] data, instruction;
    reg [64:0] serial;

    // Control Unit
    reg PCCtrl = 1'b1;
    reg RegDst, RegWrite, ALUSrc, MemRead, MemWrite, MemtoReg, gate, reset, enable, memory_enable; 

    // Cycle - State
    reg [255:0] ID, EX, MEM, WB;

    integer cnt;

    MainMemory MainMemory_CPU(  .CLOCK(clock),
                                .RESET(reset),
                                .ENABLE(memory_enable),
                                .FETCH_ADDRESS(address),
                                .EDIT_SERIAL(serial),
                                .DATA(data));

    InstructionRAM InstructionRAM_CPU(  .CLOCK(clock),
                                        .RESET(reset),
                                        .ENABLE(enable),
                                        .FETCH_ADDRESS(PC),
                                        .DATA(instruction));

    always @(start)
        begin
            register[0] = 32'h0000_0000;
            reset = 1'b0;
            memory_enable = 1'b1;
            enable = 1'b1;
            ongoing = 1'b1;

            cnt = 3;

            ID = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
            EX = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
            MEM = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
            WB = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
        end

    // Stage 1 - Instruction Fetch
    always @(posedge clock)
        begin
            // This stage mainly works to prepare for the next stage ID.
            // ID consists of 64 bits:
            // - Index [31:0] stores the instruction code
            // - Index [63:32] stores the PC address information

            //$display("Stage 1: %b", instruction);

            if(PCCtrl == 1'b1)
                begin
                    // Directly execute when Branch/Jump is executable.

                    if(jump == 1'b1)
                        begin
                            PC = jump_address;

                            ID = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            EX = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            MEM = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            
                            jump <= 1'b0;
                        end
                    else if(branch == 1'b1)
                        begin
                            PC = branch_address;

                            ID = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            EX = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            // MEM = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;
                            // WB = 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff;

                            branch <= 1'b0;
                        end
                    else
                        begin
                            PC <= PC + 1;
                        end
                    
                    ID[31:0] <= instruction;
                    ID[63:32] <= PC;
                end
            else
                begin
                    ID[31:0] <= instruction;
                    PC <= PC - 1;
                    ID[63:32] <= PC;
                end
            
            if(instruction[31:0] == 32'hffff_ffff)
                ongoing = 1'b0;

//            $display("Stage 1: %b", instruction);
        end

    // Stage 2 - Instruction Decode
    always @(posedge clock)
        begin
//            if(ID != 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff) begin
            if(cnt == 3) begin
            // This stage mainly works to prepare for the next stage EX.
            // EX consists of 130 bits:
            // - Index [31:0] stores the signed / unsigned immediate value for I-Type instruction
            // - Index [63:32] stores the register[rt] value
            // - Index [95:64] stores the register[rs] value
            // - Index [101:96] stores the func value
            // - Index [107:102] stores the opcode value
            // - Index [114:108] stores the Control Unit value
            // - Index [119:115] stores the rs value 
            // - Index [124:120] stores the rt value
            // - Index [129:125] stores the rd value for R-Type instruction
            // - Index [134:130] stores the ra value for R-Type instruction
            // - Index [166:135] stores the pc PC address information
            // - Index [192:167] stores the target address information for J-Type instruction

            opcode = ID[31:26];
            func = ID[5:0];
            // addi, addiu, lw, sw, beq, bne
            if(opcode == 6'b001000 || opcode == 6'b001001 || opcode == 6'b100011 || opcode == 6'b101011 || opcode == 6'b000100 || opcode == 6'b000101)
                EX[31:0] <= {{16{ID[15]}}, ID[15:0]};
            else
                EX[31:0] <= {{16'b0000_0000_0000_0000}, ID[15:0]};
            EX[63:32] <= register[ID[20:16]];
            EX[95:64] <= register[ID[25:21]];
            EX[101:96] <= func;
            EX[107:102] <= opcode;

            if((ID[20:16] == EX[124:120] || ID[25:21] == EX[124:120]) && MemRead == 1'b1)
                begin
                    MemtoReg = 1'b0;
                    MemWrite = 1'b0;
                    MemRead = 1'b0;
                    ALUSrc = 1'b0;
                    gate = 1'b0;
                    RegWrite = 1'b0;
                    RegDst = 1'b0;
                    PCCtrl <= 1'b0;
                end
            else
                begin
                    // lw
                    MemtoReg = (opcode == 6'b100011);
                    MemRead = (opcode == 6'b100011);
                    // sw
                    MemWrite = (opcode == 6'b101011);

                    if(opcode == 6'b000000)
                        RegDst = 1'b1;
                    else if(opcode == 6'b001000 || opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101 || opcode == 6'b100011 || opcode == 6'b001110)
                        RegDst = 1'b0;
                    
                    if(opcode == 6'b000000)
                        ALUSrc = 1'b0;
                    else if(opcode == 6'b001000 || opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101 || opcode == 6'b100011 || opcode == 6'b101011 || opcode == 6'b001110)
                        ALUSrc = 1'b1;
                    
                    RegWrite = ((opcode == 6'b000000 && func != 001000) || opcode == 6'b001000 || opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101 || opcode == 6'b100011 || opcode == 6'b001110 || opcode == 6'b000011);
                    gate = ((opcode == 6'b000000 && func != 001000) || opcode == 6'b001000 || opcode == 6'b001001 || opcode == 6'b001100 || opcode == 6'b001101 || opcode == 6'b100011 || opcode == 6'b101011 || opcode == 6'b001110);
                    PCCtrl <= 1'b1;
                end
            
            EX[114] <= RegDst;
            EX[113] <= RegWrite;
            EX[112] <= gate;
            EX[111] <= ALUSrc;
            EX[110] <= MemRead;
            EX[109] <= MemWrite;
            EX[108] <= MemtoReg;
            if(ID[15:11] != 5'b11111)
                EX[119:115] <= ID[15:11];
            else
                EX[119:115] <= 5'b00000;
            // if(opcode == 6'b000011)
            //     EX[124:120] <= 5'b11111;
            // else
            EX[124:120] <= ID[20:16];
            // if(opcode == 6'b000011)
            //     EX[129:125] <= 5'b11111;
            // else
            EX[129:125] <= ID[25:21];
            EX[134:130] <= ID[10:6];
            EX[166:135] <= ID[63:32]; 
            EX[192:167] <= ID[25:0];
//            $display("Stage 2: %b %b", opcode, func);
            end
        end

    // Stage 3 - Execution
    always @(posedge clock)
        begin
//            if(EX != 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff) begin
            if(cnt != 3)
                if(cnt == 1 || cnt == 2)
                    cnt = cnt - 1;
                else
                    cnt = 3;
            else begin
            // This stage works to execute the instruction and prepare for the next stage MEM.
            // MEM consists of 54 bits:
            // - Index [31:0] stores the register C value
            // - Index [34:32] stores the Memory Control Unit value
            // - Index [36:35] stores the Register Control Unit value
            // - Index [41:37] stores the rs value
            // - Index [46:42] stores the rt value
            // - Index [51:47] stores the rd value for R-Type instruction
            // - Index [52] stores the ALU Source Control Unit value
            // - Index [53] stores the gate Control Unit value

            cnt = 3;

            if(EX[112] == 1'b1)
                begin
                    if(EX[111] == 1'b1)
                        begin
                            register_A = register[EX[129:125]];
                            register_B = EX[31:0];
                        end
                    else
                        begin
                            register_A = register[EX[129:125]];
                            register_B = register[EX[124:120]];
                        end

                    if(MEM[52] == 1'b0 && MEM[41:37] == EX[129:125]) register_A = MEM[31:0];
                    if(WB[77] == 1'b0 && WB[71:67] == EX[129:125]) register_A = WB[31:0];
                    if(MEM[52] == 1'b1 && MEM[46:42] == EX[129:125]) register_A = MEM[31:0];
                    if(WB[77] == 1'b1 && WB[64] == 1'b0 && WB[76:72] == EX[129:125]) register_A = WB[31:0];
                    if(WB[77] == 1'b1 && WB[64] == 1'b1 && WB[76:72] == EX[129:125]) register_A = WB[63:32];

                    if(EX[111] == 1'b0)
                        begin
                            if(MEM[52] == 1'b0 && MEM[41:37] == EX[124:120]) register_B = MEM[31:0];
                            if(WB[77] == 1'b0 && WB[71:67] == EX[124:120]) register_B = WB[31:0];
                            if(MEM[52] == 1'b1 && MEM[46:42] == EX[124:120]) register_B = MEM[31:0];
                            if(WB[77] == 1'b1 && WB[64] == 1'b0 && WB[76:72] == EX[124:120]) register_B = WB[31:0];
                            if(WB[77] == 1'b1 && WB[64] == 1'b1 && WB[76:72] == EX[124:120]) register_B = WB[63:32];
                        end
                end

            // Data transfer instructions:
            // - lw
            if(EX[107:102] == 6'b100011)
                begin
                    register_C = register_A + register_B;
                end
            // - sw
            else if(EX[107:102] == 6'b101011)
                begin
                    register_C = register_A + register_B;
                    //$display(">>>>>>>>>>> SW %d", register_B);
                end

            // Arithmetic instructions:
            // - add
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100000)
                begin
                    register_C = $signed(register_A) + $signed(register_B);
                end
            // - addu
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100001)
                begin
                    register_C = $unsigned(register_A) + $unsigned(register_B);
                end
            // - addi
            else if(EX[107:102] == 6'b001000)
                begin
                    register_C = $signed(register_A) + $signed(register_B);
                    //$display(">>>>>>>>>>> ADDI, %d = %d + %d", EX[119:115], register_A, register_B);
                end
            // - addiu
            else if(EX[107:102] == 6'b001001)
                begin
                    register_C = $unsigned(register_A) + $unsigned(register_B);
                end
            // - sub
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100010)
                begin
                    register_C = $signed(register_A) - $signed(register_B);
//                    $display(">>>>>>>>>>> SUB");
                end
            // - subu
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100011)
                begin
                    register_C = $unsigned(register_A) - $unsigned(register_B);
                end

            // Logical instructions:
            // - and
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100100)
                begin
                    register_C = register_A & register_B;
                end
            // - andi
            else if(EX[107:102] == 6'b001100)
                begin
                    register_C = register_A & register_B;
                end
            // - nor
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100111)
                begin
                    register_C = ~(register_A | register_B);
                end
            // - or
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100101)
                begin
                    register_C = register_A | register_B;
                end
            // - ori
            else if(EX[107:102] == 6'b001101)
                begin
                    register_C = register_A | register_B;
                end
            // - xor
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b100110)
                begin
                    register_C = register_A ^ register_B;
                end
            // - xori
            else if(EX[107:102] == 6'b001110)
                begin
                    register_C = register_A ^ register_B;
                end

            // Shifting instructions:
            // - sll
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000000)
                begin
                    register_C = register_B << EX[134:130];
                end
            // - sllv
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000100)
                begin
                    register_C = register_B << register_A;
                end
            // - srl
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000010)
                begin
                    register_C = register_B >> EX[134:130];
                end
            // - srlv
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000110)
                begin
                    register_C = register_B >> register_A;
                end
            // - sra
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000011)
                begin
                    register_C = $signed(register_B) >>> EX[134:130];
                end
            // - srav
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b000111)
                begin
                    register_C = $signed(register_B) >>> register_A;
                end

            // Branch/Jump instructions:
            // - beq
            else if(EX[107:102] == 6'b000100)
                begin
                    //("%b %b", register_A, register_B);
                    if(register[EX[129:125]] == register[EX[124:120]])
                        begin
                            branch <= 1'b1;
//                            branch_address <= PC + EX[31:0] - 3;
                            branch_address <= EX[166:135] + EX[31:0];
                            cnt = cnt - 1;
//                            branch_address <= EX[166:135] + EX[31:0];

                            //$display("[beq] branch to %b, since %b == %b", branch_address, register[EX[129:125]], register[EX[124:120]]);
                        end
                    else
                        begin
                            //$display("[beq] doesn't branch since %b != %b", register[EX[129:125]], register[EX[124:120]]);
                        end
//                    $display(">>>>>>>>>>> BEQ");
                end
            // - bne
            else if(EX[107:102] == 6'b000101)
                begin
                    if(register[EX[129:125]] != register[EX[124:120]])
                        begin
                            branch <= 1'b1;
//                            branch_address <= PC + EX[31:0] - 3;
                            branch_address <= EX[166:135] + EX[31:0];
                            
                            cnt = cnt - 1;
//                            branch_address <= EX[166:135] + EX[31:0];

//                            $display("[bne] branch to %b, since %b != %b", branch_address, register[EX[129:125]], register[EX[124:120]]);
                        end
                    else
                        begin
//                            $display("[bne] doesn't branch since %b == %b", register[EX[129:125]], register[EX[124:120]]);
                        end
//                    $display(">>>>>>>>>>> BNE");
                end
            // - slt
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b101010)
                begin
                    if($signed(register_A) < $signed(register_B))
                        register_C = 32'b1;
                    else
                        register_C = 32'b0;
//                    $display(">>>>>>>>>>> SLT");
                end
            // - j
            else if(EX[107:102] == 6'b000010)
                begin
                    jump <= 1'b1;
                    jump_address <= EX[192:167];

                    //$display("[>>>>> j]: %d", EX[192:167]);

                    cnt = cnt - 1;
                end
            // - jr
            else if(EX[107:102] == 6'b000000 && EX[101:96] == 6'b001000)
                begin
                    jump <= 1'b1;
                    if(EX[129:125] == 5'b11111)
                        jump_address <= ra;
                    else
                        jump_address <= register[EX[129:125]] / 4;
                    // $display("[>>>>> %b]", register[EX[129:125]] / 4);
                    //$display("[>>>>> jr]: %d", ra);
                    //$display("[>>>>> jr]: %d", register[EX[129:125]] / 4);

                    cnt = cnt - 1;
                end
            // - jal
            else if(EX[107:102] == 6'b000011)
                begin
                    jump <= 1'b1;
                    jump_address <= EX[192:167];

                    //$display("[>>>>> jal]: %d", EX[192:167]);
                    //$display("[>>>>> jal]: %d", EX[166:135]);

                    cnt = cnt - 1;
                    register_A = 5'b11111;
                    register_B = 5'b11111;
                    register_C = EX[166:135];
//                    register[31] = register_C;
                    ra = register_C;
                end
            
            MEM[31:0] <= register_C;
            MEM[34:32] <= EX[110:108];
            MEM[36:35] <= EX[114:113];
            MEM[41:37] <= EX[119:115];
            MEM[46:42] <= EX[124:120];
            MEM[51:47] <= EX[129:125];
            MEM[53:52] <= EX[112:111];

            //$display("Stage 3: %b %b = %b, allow: %b", register_A, register_B, register_C, EX[109]);
            //$display("Stage 3: %b %b", opcode, func);
            end
        end

    // Stage 4 - Access Memory
    always @(posedge clock)
        begin 
            if(MEM != 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff) begin 
            // This stage mainly works to prepare for the last stage WB.
            // WB consists of 79 bits:
            // - Index [31:0] stores the register C value
            // - Index [63:32] stores the Load Data value
            // - Index [64] stores the Memory to Register Control Unit value
            // - Index [66:65] stores the Register Control Unit value
            // - Index [71:67] stores the rs value
            // - Index [76:72] stores the rt value
            // - Index [77] stores the ALU Source Control Unit value
            // - Index [78] stores the gate Control Unit value


            if(MEM[33] == 1'b1 && MEM[34:32] != 3'b111)
                begin
                    address = MEM[31:0] / 4;
                    serial = {1'b1, address, register[MEM[46:42]]};
                    //$display("[ MEMORY WRITE ], address = ", address, ", %b", serial[31:0], ", ", serial[64]);
                end
            else if(MEM[34] == 1'b1 && MEM[34:32] != 3'b111)
                begin
                    address = MEM[31:0] / 4;
                    serial = {1'b0, address, register[MEM[46:42]]};
                    //$display("[ MEMORY READ], address = ", address, ", %b", data);
                end
            

            WB[31:0] <= MEM[31:0];
            WB[63:32] = data;
            WB[64] <= MEM[32];
            WB[66:65] <= MEM[36:35];
            WB[71:67] <= MEM[41:37];
            WB[76:72] <= MEM[46:42];
            WB[78:77] <= MEM[53:52];

            //$display("Stage 4: %b %b", data, MEM[33]);
            end
        end

    // Stage 5 - Write Back
    always @(posedge clock)
        begin
            if(WB != 256'hffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff_ffff) begin
            //$display("Stage 5: %b", WB[65]);

            if(WB[65] == 1'b1)
                begin
                    if(WB[66] == 1'b1 && WB[64] == 1'b1 && WB[71:67] != 5'b11111)        register[WB[71:67]] <= WB[63:32];
                    else if(WB[66] == 1'b1 && WB[64] == 1'b0 && WB[71:67] != 5'b11111)   register[WB[71:67]] <= WB[31:0];
                    else if(WB[66] == 1'b0 && WB[64] == 1'b1 && WB[76:72] != 5'b11111)   register[WB[76:72]] <= WB[63:32];
                    else if(WB[66] == 1'b0 && WB[64] == 1'b0 && WB[76:72] != 5'b11111)   register[WB[76:72]] <= WB[31:0];

                    // if(WB[66] == 1'b1 && WB[64] == 1'b1 && WB[71:67] != 5'b11111)        $display("[%b <= %b]", WB[71:67], WB[63:32]);
                    // else if(WB[66] == 1'b1 && WB[64] == 1'b0 && WB[71:67] != 5'b11111)   $display("[%b <= %b]", WB[71:67], WB[31:0]);
                    // else if(WB[66] == 1'b0 && WB[64] == 1'b1 && WB[76:72] != 5'b11111)   $display("[%b <= %b]", WB[76:72], WB[63:32]);
                    // else if(WB[66] == 1'b0 && WB[64] == 1'b0 && WB[76:72] != 5'b11111)   $display("[%b <= %b]", WB[76:72], WB[31:0]);

                    register[31] <= ra;
                end
            end
        end

endmodule