module Lab9(input CLOCK_50, input [9:0]SW, output[9:0]LEDR, input [3:0] KEY, output [6:0] HEX0,output [6:0] HEX1,output [6:0] HEX2,output [6:0] HEX3,output [6:0] HEX4,output [6:0] HEX5);


	Lab8HW u0 (
		.clk_clk       (CLOCK_50),       //   clk.clk
		.key_export    (KEY),    //   key.export
		.ledr_export   (LEDR),   //  ledr.export
		.reset_reset_n (1'b1), // reset.reset_n
		.sw_export     (SW),      //    sw.export
		.hex0_export   (HEX0),   //  hex0.export
		.hex1_export   (HEX1),   //  hex1.export
		.hex2_export   (HEX2),   //  hex2.export
		.hex3_export   (HEX3),   //  hex3.export
		.hex4_export   (HEX4),   //  hex4.export
		.hex5_export   (HEX5)    //  hex5.export
	);

endmodule
	