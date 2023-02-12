#ifndef util_h
#define util_h
#define SET_BIT(var,bitpos)    (var=var |(1<<bitpos))
#define CLR_BIT(var,bitpos)  (var =var &~(1<<bitpos))
#define toggle_bit(var,bitpos) (var=var ^ (1<<bitpos))
#define GET_BIT(var,bitpos)   ((1&(var>>bitpos)))
#define Assign_Bit(Var,Bit_No,Value) do{if(Value == 1) SET_BIT(Var,Bit_No); \
										else CLR_BIT(Var,Bit_No);}while(0)
#define SET_BYTE (reg,value)	(reg=value)
#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0)  Conc_help(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_help(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0


#endif
