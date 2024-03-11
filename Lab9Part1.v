module Lab9(input CLOCK_50, input [9:0]SW, output[9:0]LEDR, input [3:0] KEY);

Lab8HW u0 (
		.clk_clk       (CLOCK_50),       //   clk.clk
		.reset_reset_n (1'b1), // reset.reset_n
		.sw_export     (SW),     //    sw.export
		.ledr_export   (LEDR),   //  ledr.export
		.key_export    (KEY)     //   key.export
	);
endmodule
	