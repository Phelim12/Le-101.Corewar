echo "\n\nMASM 42.s\n\n"
valgrind ./asm   ./MASM/42.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM barriere.s\n\n"
valgrind ./asm   ./MASM/barriere.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM empty.s\n\n"
valgrind ./asm   ./MASM/empty.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_direct.s\n\n"
valgrind ./asm   ./MASM/lexer_direct.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_direct_number1.s\n\n"
valgrind ./asm   ./MASM/lexer_direct_number1.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_direct_number2.s\n\n"
valgrind ./asm   ./MASM/lexer_direct_number2.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_direct_number3.s\n\n"
valgrind ./asm   ./MASM/lexer_direct_number3.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_dot.s\n\n"
valgrind ./asm   ./MASM/lexer_dot.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_indirect_number1.s\n\n"
valgrind ./asm   ./MASM/lexer_indirect_number1.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_indirect_number2.s\n\n"
valgrind ./asm   ./MASM/lexer_indirect_number2.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_indirect_number3.s\n\n"
valgrind ./asm   ./MASM/lexer_indirect_number3.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_indirect_number4.s\n\n"
valgrind ./asm   ./MASM/lexer_indirect_number4.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_label1.s\n\n"
valgrind ./asm   ./MASM/lexer_label1.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM lexer_unexpected_char.s\n\n"
valgrind ./asm   ./MASM/lexer_unexpected_char.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser.s\n\n"
valgrind ./asm   ./MASM/parser.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_bad_number_param.s\n\n"
valgrind ./asm   ./MASM/parser_bad_number_param.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_bad_param.s\n\n"
valgrind ./asm   ./MASM/parser_bad_param.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_more_3_param.s\n\n"
valgrind ./asm   ./MASM/parser_more_3_param.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_name_empty.s\n\n"
valgrind ./asm   ./MASM/parser_name_empty.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_need_param.s\n\n"
valgrind ./asm   ./MASM/parser_need_param.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_no_comment.s\n\n"
valgrind ./asm   ./MASM/parser_no_comment.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_no_eof_into_cmd.s\n\n"
valgrind ./asm   ./MASM/parser_no_eof_into_cmd.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_no_label_dec.s\n\n"
valgrind ./asm   ./MASM/parser_no_label_dec.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_no_name.s\n\n"
valgrind ./asm   ./MASM/parser_no_name.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_no_param.s\n\n"
valgrind ./asm   ./MASM/parser_no_param.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_same_label_dec.s\n\n"
valgrind ./asm   ./MASM/parser_same_label_dec.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_same_label_dec2.s\n\n"
valgrind ./asm   ./MASM/parser_same_label_dec2.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_too_many_label_dec.s\n\n"
valgrind ./asm   ./MASM/parser_too_many_label_dec.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_two_comment.s\n\n"
valgrind ./asm   ./MASM/parser_two_comment.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_two_name.s\n\n"
valgrind ./asm   ./MASM/parser_two_name.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unclose_string.s\n\n"
valgrind ./asm   ./MASM/parser_unclose_string.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unclose_string2.s\n\n"
valgrind ./asm   ./MASM/parser_unclose_string2.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unexpected_token.s\n\n"
valgrind ./asm   ./MASM/parser_unexpected_token.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unexpected_token2.s\n\n"
valgrind ./asm   ./MASM/parser_unexpected_token2.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unexpected_token3.s\n\n"
valgrind ./asm   ./MASM/parser_unexpected_token3.s
echo "\n----------------------------------------\n"
sleep 4
echo "\n\nMASM parser_unknow_cmd.s\n\n"
valgrind ./asm   ./MASM/parser_unknow_cmd.s
echo "\n----------------------------------------\n"
sleep 4