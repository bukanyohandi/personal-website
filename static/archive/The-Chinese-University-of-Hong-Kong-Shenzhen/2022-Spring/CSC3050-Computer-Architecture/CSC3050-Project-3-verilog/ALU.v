module alu(instruction, regA, regB, result, flags);

    // Input
    // Note: the address of regA is 00000, the address of regB is 00001
    input signed[31:0] instruction, regA, regB;

    // Output, Flags
    // Note: the first bit is zero flag, the second bit is negative, and the
    //       third bit is overflow flag 
    output[31:0] result;
    output[2:0] flags;

    // Constants
    wire[0:0] zero = 1'b0;
    wire[0:0] one = 1'b1;

    // Variables
    reg[5:0] opcode, func;
    reg[31:0] calculate, rs, rt;
    reg[2:0] tmp;

    always @(instruction, regA, regB)
    begin

        // calculate = 32'bX;
        tmp = {3{zero}};

        opcode = instruction[31:26];
        func = instruction[5:0];

        rs = 0;
        if(instruction[25:21] == 5'b00000)
            begin
                rs = regA;
            end
        else if(instruction[25:21] == 5'b00001)
            begin
                rs = regB;
            end

        rt = 0;
        if(instruction[20:16] == 5'b00000)
            begin
                rt = regA;
            end
        else if(instruction[20:16] == 5'b00001)
            begin
                rt = regB;
            end

        // $display("%b", regA);
        // $display("%b", regB);

        case(opcode)

        // R-Type Instructions:
        // add, addu;
        // sub, subu;
        // and, nor, or, xor;
        // slt, sltu;
        // ;
        // sll, sllv, srl, srlv, sra, srav;
        6'b000000:
        begin
            case(func)
            
            // add
            6'b100000:
            begin
                calculate = rs + rt;
                tmp[0] = ((calculate[31] != rs[31]) && (rs[31] == rt[31]));
            end
            
            // addu
            6'b100001:
            begin
                calculate = rs + rt;
            end

            // sub
            6'b100010:
            begin
                calculate = rs - rt;
                tmp[0] = ((calculate[31] != rs[31]) && (rs[31] != rt[31]));
            end

            // subu
            6'b100011:
            begin
                calculate = rs - rt;
            end

            // and
            6'b100100:
            begin
                calculate = rs & rt;
            end

            // nor
            6'b100111:
            begin
                calculate = ~(rs | rt);
            end

            // or
            6'b100101:
            begin
                calculate = rs | rt;
            end

            // xor
            6'b100110:
            begin
                calculate = rs ^ rt;
            end

            // slt
            6'b101010:
            begin
                calculate = $signed(rs) - $signed(rt);
                if($signed(rs) < $signed(rt))
                    begin
                        tmp[1] = 1;
                    end
            end

            // sltu
            6'b101011:
            begin
                calculate = rs - rt;
                if(rs < rt)
                    begin
                        tmp[1] = 1;
                    end
            end

            // sll
            6'b000000:
            begin
                calculate = rt << instruction[10:6];
            end

            // sllv
            6'b000100:
            begin
                calculate = rt << rs;
            end

            // srl
            6'b000010:
            begin
                calculate = rt >> instruction[10:6];
            end

            // srlv
            6'b000110:
            begin
                calculate = rt >> rs;
            end

            // sra
            6'b000011:
            begin
                calculate = $signed(rt) >>> instruction[10:6];
            end

            // srav
            6'b000111:
            begin
                calculate = $signed(rt) >>> rs;
            end

            endcase
        end

        // I-Type Instructions:
        // addi, addiu;
        // ;
        // andi, ori, xori;
        // beq, bne, slti, sltiu;
        // lw, sw;
        // ;

        // addi
        6'b001000:
        begin
            calculate = rs + {{16{instruction[15]}}, instruction[15:0]};
            tmp[0] = ((calculate[31] != rs[31]) && (rs[31] == instruction[15]));
        end

        // addiu
        6'b001001:
        begin
            calculate = rs + {{16{instruction[15]}}, instruction[15:0]};
        end

        // andi
        6'b001100:
        begin
            calculate = rs & {{16{zero}}, instruction[15:0]};
        end

        // ori
        6'b001101:
        begin
            calculate = rs | {{16{zero}}, instruction[15:0]};
        end

        // xori
        6'b001110:
        begin
            calculate = rs ^ {{16{zero}}, instruction[15:0]};
        end

        // beq
        6'b000100:
        begin
            calculate = $signed(rs) - $signed(rt);
            if(calculate == 0)
                begin
                    tmp[2] = 1;
                end
        end

        // bne
        6'b000101:
        begin
            calculate = $signed(rs) - $signed(rt);
            if(calculate != 0)
                begin
                    tmp[2] = 1;
                end
        end

        // slti
        6'b001010:
        begin
            calculate = $signed(rs) - $signed({{16{instruction[15]}}, instruction[15:0]});
            if($signed(rs) < $signed({{16{instruction[15]}}, instruction[15:0]}))
                begin
                    tmp[1] = 1;
                end
        end

        // sltiu
        6'b001011:
        begin
            calculate = rs - {{16{instruction[15]}}, instruction[15:0]};
            if(rs < {{16{instruction[15]}}, instruction[15:0]})
                begin
                    tmp[1] = 1;
                end
        end

        // lw
        6'b100011:
        begin
            calculate = $signed(rs) + $signed({{16{instruction[15]}}, instruction[15:0]});
        end

        // sw
        6'b101011:
        begin
            calculate = $signed(rs) + $signed({{16{instruction[15]}}, instruction[15:0]});
        end

        endcase

    end

    assign flags[2] = (tmp[2] == 1);
    assign flags[1] = (tmp[1] == 1);
    assign flags[0] = (tmp[0] == 1);
    assign result = calculate[31:0];

endmodule