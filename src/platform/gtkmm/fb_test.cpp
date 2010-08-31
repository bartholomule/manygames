#include <iostream>
using std::cout;
using std::endl;

/*
 * $Id$
 *
 * Part of "Many Games" - A nearly infinitely expandable gaming framework
 * Copyright (C) 2003 Kevin Harris
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <manygames/manygames_config.hpp>
#include <manygames/textized.hpp>
#include "gtkmm_input_window.hpp"
#include <manygames/xpm_image_loader.hpp>
#include <sys/time.h>

static manygames::masked_image<unsigned char,bool> barf;
int x_shift, y_shift;

const char *const wheelbarrow_xpm[] =
	{
		"48 48 64 1",
		"       c None",
		".      c #DF7DCF3CC71B",
		"X      c #965875D669A6",
		"o      c #71C671C671C6",
		"O      c #A699A289A699",
		"+      c #965892489658",
		"@      c #8E38410330C2",
		"#      c #D75C7DF769A6",
		"$      c #F7DECF3CC71B",
		"%      c #96588A288E38",
		"&      c #A69992489E79",
		"*      c #8E3886178E38",
		"=      c #104008200820",
		"-      c #596510401040",
		";      c #C71B30C230C2",
		":      c #C71B9A699658",
		">      c #618561856185",
		",      c #20811C712081",
		"<      c #104000000000",
		"1      c #861720812081",
		"2      c #DF7D4D344103",
		"3      c #79E769A671C6",
		"4      c #861782078617",
		"5      c #41033CF34103",
		"6      c #000000000000",
		"7      c #49241C711040",
		"8      c #492445144924",
		"9      c #082008200820",
		"0      c #69A618611861",
		"q      c #B6DA71C65144",
		"w      c #410330C238E3",
		"e      c #CF3CBAEAB6DA",
		"r      c #71C6451430C2",
		"t      c #EFBEDB6CD75C",
		"y      c #28A208200820",
		"u      c #186110401040",
		"i      c #596528A21861",
		"p      c #71C661855965",
		"a      c #A69996589658",
		"s      c #30C228A230C2",
		"d      c #BEFBA289AEBA",
		"f      c #596545145144",
		"g      c #30C230C230C2",
		"h      c #8E3882078617",
		"j      c #208118612081",
		"k      c #38E30C300820",
		"l      c #30C2208128A2",
		"z      c #38E328A238E3",
		"x      c #514438E34924",
		"c      c #618555555965",
		"v      c #30C2208130C2",
		"b      c #38E328A230C2",
		"n      c #28A228A228A2",
		"m      c #41032CB228A2",
		"M      c #104010401040",
		"N      c #492438E34103",
		"B      c #28A2208128A2",
		"V      c #A699596538E3",
		"C      c #30C21C711040",
		"Z      c #30C218611040",
		"A      c #965865955965",
		"S      c #618534D32081",
		"D      c #38E31C711040",
		"F      c #082000000820",
		"                                                ",
		"          .XoO                                  ",
		"         +@#$%o&                                ",
		"         *=-;#::o+                              ",
		"           >,<12#:34                            ",
		"             45671#:X3                          ",
		"               +89<02qwo                        ",
		"e*                >,67;ro                       ",
		"ty>                 459@>+&&                    ",
		"$2u+                  ><ipas8*                  ",
		"%$;=*                *3:.Xa.dfg>                ",
		"Oh$;ya             *3d.a8j,Xe.d3g8+             ",
		" Oh$;ka          *3d$a8lz,,xxc:.e3g54           ",
		"  Oh$;kO       *pd$%svbzz,sxxxxfX..&wn>         ",
		"   Oh$@mO    *3dthwlsslszjzxxxxxxx3:td8M4       ",
		"    Oh$@g& *3d$XNlvvvlllm,mNwxxxxxxxfa.:,B*     ",
		"     Oh$@,Od.czlllllzlmmqV@V#V@fxxxxxxxf:%j5&   ",
		"      Oh$1hd5lllslllCCZrV#r#:#2AxxxxxxxxxcdwM*  ",
		"       OXq6c.%8vvvllZZiqqApA:mq:Xxcpcxxxxxfdc9* ",
		"        2r<6gde3bllZZrVi7S@SV77A::qApxxxxxxfdcM ",
		"        :,q-6MN.dfmZZrrSS:#riirDSAX@Af5xxxxxfevo",
		"         +A26jguXtAZZZC7iDiCCrVVii7Cmmmxxxxxx%3g",
		"          *#16jszN..3DZZZZrCVSA2rZrV7Dmmwxxxx&en",
		"           p2yFvzssXe:fCZZCiiD7iiZDiDSSZwwxx8e*>",
		"           OA1<jzxwwc:$d%NDZZZZCCCZCCZZCmxxfd.B ",
		"            3206Bwxxszx%et.eaAp77m77mmmf3&eeeg* ",
		"             @26MvzxNzvlbwfpdettttttttttt.c,n&  ",
		"             *;16=lsNwwNwgsvslbwwvccc3pcfu<o    ",
		"              p;<69BvwwsszslllbBlllllllu<5+     ",
		"              OS0y6FBlvvvzvzss,u=Blllj=54       ",
		"               c1-699Blvlllllu7k96MMMg4         ",
		"               *10y8n6FjvllllB<166668           ",
		"                S-kg+>666<M<996-y6n<8*          ",
		"                p71=4 m69996kD8Z-66698&&        ",
		"                &i0ycm6n4 ogk17,0<6666g         ",
		"                 N-k-<>     >=01-kuu666>        ",
		"                 ,6ky&      &46-10ul,66,        ",
		"                 Ou0<>       o66y<ulw<66&       ",
		"                  *kk5       >66By7=xu664       ",
		"                   <<M4      466lj<Mxu66o       ",
		"                   *>>       +66uv,zN666*       ",
		"                              566,xxj669        ",
		"                              4666FF666>        ",
		"                               >966666M         ",
		"                                oM6668+         ",
		"                                  *4            ",
		"                                                ",
		"                                                "
	};

static const char* const al_xpm[] = {
	"20 20 6 1",
	//"     c #000000000000",
	"       c None",
	".      c #FFFF8E8E5757",
	"X      c #BFBF6A6A4141",
	"o      c #FFFF84848E8E",
	"O      c #BFBF63636A6A",
	"+      c #FFFFFFFFFFFF",
	"                    ",
	"                    ",
	"                    ",
	"    .   .  .   .    ",
	"    X...X  X...X    ",
	"     ..      ..     ",
	"     X.XooooX.X     ",
	"      X. oo .X      ",
	"       . oo .       ",
	"   OooOo++++oOooO   ",
	"   oOOOooooooOOOo   ",
	"       +oooo+       ",
	"     OoO++++OoO     ",
	"     oO      Oo     ",
	"     oO      Oo     ",
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                    "};


static const char* const barf_xpm[] = {
	/* width height ncolors chars_per_pixel */
	"70 40 248 2",
	/* colors */
	"   c #000000",
	" . c #741723",
	" X c #9B1E2F",
	" o c #D8344A",
	" O c #4635B2",
	" + c #F3C0C7",
	" @ c #ABABAB",
	" # c #D42E46",
	" $ c #766DAC",
	" % c #D73F56",
	" & c #A3A3A3",
	" * c #3F30A1",
	" = c #AE2952",
	" - c #BD2539",
	" ; c #665D9C",
	" : c #999999",
	" > c #CB2B4A",
	" , c #E47180",
	" < c #451E54",
	" 1 c #89244B",
	" 2 c #919191",
	" 3 c #D93C51",
	" 4 c #3C2D97",
	" 5 c #9C4E8F",
	" 6 c #8B8B8B",
	" 7 c #CBC8E1",
	" 8 c #2C2170",
	" 9 c #392C8A",
	" 0 c #D52B43",
	" q c #838383",
	" w c #5445B5",
	" e c #352886",
	" r c #4233A0",
	" t c #DE5366",
	" y c #3E2F9C",
	" u c #28080C",
	" i c #9C1F2F",
	" p c #463D7C",
	" a c #79318A",
	" s c #403776",
	" d c #3E3574",
	" f c #39316F",
	" g c #696969",
	" h c #E67D8B",
	" j c #BF263A",
	" k c #EA909C",
	" l c #D53149",
	" z c #290E27",
	" x c #DBD7F0",
	" c c #312967",
	" v c #6C49AB",
	" b c #C58EB3",
	" n c #6B5DC1",
	" m c #2B2361",
	" M c #2A2160",
	" N c #A02139",
	" B c #852D71",
	" V c #4F3FB6",
	" C c #281F5E",
	" Z c #D93B50",
	" A c #251D5B",
	" S c #241B5A",
	" D c #575757",
	" F c #231B59",
	" G c #555555",
	" H c #6E296E",
	" J c #D12D48",
	" K c #4333AA",
	" L c #D98AA2",
	" P c #C42B4F",
	" I c #D52A42",
	" U c #F1B8C0",
	" Y c #D42A41",
	" T c #B02C59",
	" R c #CD2B44",
	" E c #4D4D4D",
	" W c #9086D1",
	" Q c #0E0A23",
	" ! c #474747",
	" ~ c #B73663",
	" ^ c #F2F2F2",
	" / c #DAA4BD",
	" ( c #783088",
	" ) c #F0F0F0",
	" _ c #CA4465",
	" ` c #393939",
	" ' c #333333",
	" ] c #5F52B1",
	" [ c #776FAE",
	" { c #65141F",
	" } c #F6D3D8",
	" | c #2B2B2B",
	".  c #6F67A6",
	".. c #252525",
	".X c #A29AD8",
	".o c #6B63A2",
	".O c #D4D4D4",
	".+ c #A098D6",
	".@ c #1D1D1D",
	".# c #9B92D1",
	".$ c #1B1B1B",
	".% c #D62B42",
	".& c #4232A8",
	".* c #191919",
	".= c #B12B59",
	".- c #C6C6C6",
	".; c #DE5164",
	".: c #9088C6",
	".> c #9F1F30",
	"., c #111111",
	".< c #7467C5",
	".1 c #8D84C3",
	".2 c #574F8E",
	".3 c #0D0D0D",
	".4 c #5849BA",
	".5 c #B22D5D",
	".6 c #070707",
	".7 c #B8B8B8",
	".8 c #E88895",
	".9 c #D0293F",
	".0 c #EC9BA6",
	".q c #030303",
	".w c #8178B7",
	".e c #010101",
	".r c #7F76B5",
	".t c #3D2F9C",
	".y c #FDF4F5",
	".u c #AEAEAE",
	".i c #7970AF",
	".p c #ACACAC",
	".a c #62339C",
	".s c #DB465A",
	".d c #8D1C2B",
	".f c #BE5D86",
	".g c #A8A8A8",
	".h c #C12C51",
	".j c #6D64A3",
	".k c #A594D0",
	".l c #CD2E4C",
	".z c #2A206B",
	".x c #D62A41",
	".c c #AC2A53",
	".v c #909090",
	".b c #A02A5B",
	".n c #A12031",
	".m c #D03652",
	".M c #8C8C8C",
	".N c #5934A3",
	".B c #C8496B",
	".V c #D72E45",
	".C c #868686",
	".Z c #382B89",
	".A c #4A287D",
	".S c #D42A42",
	".D c #828282",
	".F c #912D6D",
	".G c #AA2133",
	".H c #4D4483",
	".J c #6455BE",
	".K c #7C7C7C",
	".L c #B83865",
	".P c #62353B",
	".I c #9B274F",
	".U c #413877",
	".Y c #DB4559",
	".T c #3C317C",
	".R c #D32A44",
	".E c #C12B50",
	".W c #D12A42",
	".Q c #312867",
	".! c #646464",
	".~ c #606060",
	".^ c #BEB8E4",
	"./ c #CB4160",
	".( c #2B2261",
	".) c #5C5C5C",
	"._ c #AD2953",
	".` c #4E3EB5",
	".' c #7B1825",
	".] c #271E5D",
	".[ c #AF396C",
	".{ c #251C5B",
	".} c #A9669E",
	".| c #A7274D",
	"X  c #545454",
	"X. c #D72D44",
	"XX c #505050",
	"Xo c #D62D43",
	"XO c #4232A9",
	"X+ c #FFFFFF",
	"X@ c #CE2A45",
	"X# c #E88693",
	"X$ c #4A4A4A",
	"X% c #FBFBFB",
	"X& c #484848",
	"X* c #F9F9F9",
	"X= c #975196",
	"X- c #F5F5F5",
	"X; c #D73147",
	"X: c #FAE3E6",
	"X> c #7F53A9",
	"X, c #613CA6",
	"X< c #4C0F17",
	"X1 c #E3E3E3",
	"X2 c #6053B2",
	"X3 c #9C3373",
	"X4 c #303030",
	"X5 c #DC485C",
	"X6 c #382A8E",
	"X7 c #2C2C2C",
	"X8 c #EDA1AB",
	"X9 c #DBDBDB",
	"X0 c #F1B4BC",
	"Xq c #CE3B58",
	"Xw c #242424",
	"Xe c #31257D",
	"Xr c #A199D7",
	"Xt c #5C4EBB",
	"Xy c #9D95D3",
	"Xu c #4B3F9D",
	"Xi c #1A1A1A",
	"Xp c #D62C42",
	"Xa c #D62A42",
	"Xs c #D52A41",
	"Xd c #181818",
	"Xf c #605897",
	"Xg c #E88592",
	"Xh c #C7C7C7",
	"Xj c #4F40AE",
	"Xk c #121212",
	"Xl c #E37F8D",
	"Xz c #B43C5F",
	"Xx c #3D318F",
	"Xc c #0E0E0E",
	"Xv c #BFBFBF",
	"Xb c #8B83C1",
	"Xn c #1D0609",
	"Xm c #4D34AC",
	"XM c #0C0C0C",
	"XN c #B179AB",
	"XB c #392D8B",
	"XV c #867DBC",
	"XC c #C32B50",
	"XZ c #C22B4F",
	"XA c #4E4685",
	"XS c #952C68",
	"XD c #040404",
	"XF c #C12844",
	/* pixels */
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ O.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ n W.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X%X1.7 :.C.D.M &Xh )X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ x n.X.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X-.O &.~ '.@XcXD.e.6Xk.. !.C.OX-X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.X.X.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X9.vX$Xd.q                .e.3 ` 6X9X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ OX+.X.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X*Xh g.*                            XM DXvX*X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.XX+X+ n xX+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+Xh GXM                                .qX4 @X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.XX+X+ W.4X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X9 g.3                                    .e | @X*X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ OX+X+X+ OX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X- 2.$                                        .eX4XvX+X+X+X+X+X+X+X+X+.X.<.<.<.<.<.<.X.X.XX+X+.X.XX+X+.X.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+.OX                                          Q F AXA.:X+X+X+X+X+X+X+X+.X.<.<.<.<.<.<.4 WXtXt.X.X.XX+X+.X.XX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+.pX7                          XnX< ..d i.|.= T =._.5XzXlX0X:X+X+X+X+X+X+X+X+X+X+X+ x W.4 OXt.X OX+X+X+ OX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+ 2.,                         u.' - YXs.x.x.x.x.x.x.x.x.%X;X5 h +.yX+X+X+X+ x.X.X n n.X.X O.X.X.XX+X+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+ q.q                       z 1X@.x.x.x.x.x.x.x.x.x.x.x.x.x.xXp o.;.8 /.k n n.X.X xX+X+.X.XX+.X.XX+X+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+ q.q              .z.t.tXO (.h.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x J./ L }X+X+X+X+X+ O.XX+ O.XX+X+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+ 2.,   F F F F eX6 *.t.tX6 B.W.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.xXo 3 t , k +.k.XX+.<.<.<.XX+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+.i f O F F F F e Q         {.9.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.xXpXC 5Xm.<Xt.<.XX+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+.X.X.X.X.< O.1.H                       H.E.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x 0 _.aX+.X.XX+.X.XX+X+X+X+",
	"X+X+X+X+X+X+X+X+.X.<.<.<Xt.XXy.o.Q F F F F F F F F e O.NXSX@.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.xXa.m U.X.XX+ O.XX+X+X+X+",
	"X+X+X+X+X+X+X+.X.X.X.X.X.X.X.X.:.2 M F F F F F e O K K F < 1XF.SXs.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.sXN.X OX+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+Xh G.3     8Xe e O Q   F F.A a.F.b N X.n.>.5.G j.W.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.%.B v.XX+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X*Xh g.$   4 4 F e F O F O e e.z         F F  XnX<.IXZ.R.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x.x ZX=.XX+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X9.o O.T 9 O F F   F F               F F      Xn H.c RXs.x.x.x.x.x.x.x.x.x.x.x.x.x.xX..0X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.X O.` w ]XjXf c S F e e F F F e e e e.t.t e e e F   S.{.PX#Xq #XaXa.x.x.x.x.x.x.x.x.x.x.V.0X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X O.X.XX+ W.X.X.X.X.j.( F e e e e O e e e e.t.t e e e F   S CXXX+X:X0.f.[ ~ % I.x.x.x.x.x.x.x.YX0X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+ x O.XX+X+X+X+X+X+X+X+X+ 7 p F.t O F F           F F F F F F F eXB.KX+X+X+X+ O n.XX8.l.%.x.x.x.x lXgX:X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+ n nX+X+X+X+X+X+X+X+.X.< V.4X2Xx.& e F F F F F F.z.t.t.t.t.t.t y y r.wX+X+X+ n xX+.X n b.L >X..V PX3X>X+X+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+.X WX+X+X+X+X+X+X+X+X+.X.< n.X.X.  9 e F F e e e K * e e e e e e e.ZXu.#X+X+ x nX+X+X+ x.4X,.}.0.0X0.N n.XX+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+.X.XX+X+X+X+X+X+X+X+X+X+X+X+X+X+ ^ ;.(     F e eX6 F F F F F S S.].UXV.X.X.X OX+X+X+X+X+.X n.4 n xX+X+ O.XX+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+.X.XX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.g O F F F F F F F F F S S.] d $.X.X.X.<.<X+X+X+X+X+.X O.X x n n x.X OX+X+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+.X.XX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+XrXb.) m          .e.e.eXM E.uX-X+X+.X.<.<X+X+X+X+X+.X.XX+X+X+ x n.XXt OX+X+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+.X.< xX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ O [.! sXi.6.q.3XwX&.K.-X+X+X+X+X+.X.XX+X+X+X+X+X+X+X+X+X+X+.X.X n V OX+X+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+.X n nX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.+ O.r :.C.D.M &Xh )X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.X.4 x OX+X+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+ x O.X.X.X.X.X.X.X.X.X.X.X.X.X.X O.X.X.<.XX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ x n n xX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.X.X.X.X.X.X.X.X.X.X.X.X.X.XX+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ n.^ nX+X+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ O n xX+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ x.J nX+X+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+ n x OX+",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X.< W.X",
	"X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+X+.X V.4.X"
};





#include <gtkmm/main.h>

using namespace manygames;

// icky, nasty, global variable...
input_window<unsigned char>* fb;

void update()
{

	framebuffer<unsigned char>* fb2 = fb;

	int width,height;

	width = fb2->get_width();
	height = fb2->get_height();

	//  printf("::update called (size=[%d,%d])\n", width, height);

	if( (width == 0) || (height == 0) )
	{
		return;
	}


	//  printf("Inside update: x shift=%d, y shift=%d\n", x_shift, y_shift);

	static const manygames::rgbcolor<unsigned char> green(0,255,0);
	static const manygames::rgbcolor<unsigned char> blue(0,0,255);
	for(int y = 0; y < height; ++y)
	{
		int effective_y = (y - y_shift);
		int distance = 0;
		for(int x = 0; x < width; ++x)
		{
			int effective_x = (x - x_shift);
			//      if( (effective_y << 1) & (effective_x << 1) )
			if( effective_y & effective_x )
			{
				static int last_width = 0;
				static manygames::rgbcolor<unsigned char>* precalculated_color_gradient = NULL;

				if( (width != last_width) || !precalculated_color_gradient )
				{
					//      printf("Recalculating gradient\n");
					// Deleting NULL is safe!
					delete[] precalculated_color_gradient;

					last_width = width;
					precalculated_color_gradient = new manygames::rgbcolor<unsigned char>[width];

					const double fraction = 1.0 / 3.0;
					for( int dist = 0; dist < width; ++dist)
					{
						int value = int(fraction * 255 +
							((255 *(1 - fraction)) * dist / float(width)));
						precalculated_color_gradient[dist] = manygames::rgbcolor<unsigned char>(0, value, 0);
					}
					//      printf("Gradient calculated...\n");
				}

				//      printf("Setting pixel from gradient\n");
				fb2->setpixel_back(x,y,precalculated_color_gradient[distance]);
				++distance;

				//      setpixel_back(x,y,green);
			}
			else
			{
				fb2->setpixel_back(x,y,blue);
				distance = 0;
			}
			/*
			// Add a red 'fogging'.
			setpixel_back(x,y,manygames::rgbacolor<unsigned char,double>(128,0,0,0.5));
			*/

		}
	}
	//  printf("Everything should be drawn now...\n");
	if( !barf.empty() )
	{
		int x_mid = (int(width) - int(barf.get_width())) / 2;
		int y_mid = (int(height) - int(barf.get_height())) / 2;
		//    printf("Trying masked at %d,%d\n", x_mid, y_mid);
		fb2->bg_draw_image(barf, x_mid, y_mid);
		//    printf("Trying non-trasparent at %d,%d\n", x_mid, y_mid + barf.get_height());
		fb2->bg_draw_image(*static_cast<manygames::image<unsigned char>*>(&barf), x_mid, y_mid + barf.get_height());
	}

	//  printf("About to flip...\n");
	fb2->flip();
	//  printf("flipped!\n");
}


bool mouse_moved(int x, int y, int dx, int dy)
{
	static long last_time = time(NULL);

	//  printf("::mouse_moved(%d,%d,%d,%d)\n", x,y,dx,dy);

	unsigned buttons_down = fb->get_button_state() & mouse_input::mouse_button_mask;

	if( buttons_down != 0 )
	{
		x_shift += dx;
		y_shift += dy;

		static timeval last_time = {0,0};
		const unsigned max_fps = 15;
		const int min_us_wait = int(1000000 / double(max_fps));

		timeval t;
		gettimeofday(&t, NULL);

		long us_diff = (t.tv_usec - last_time.tv_usec);

		if( t.tv_sec > last_time.tv_sec )
		{
			us_diff += 1000000;
		}

		if( us_diff > min_us_wait )
		{
			//      printf("td=%d, min=%d\n", us_diff, min_us_wait);

			last_time.tv_sec = t.tv_sec;
			last_time.tv_usec = t.tv_usec;

			fb->update();
			fb->draw();
		}
	}
	return true;
}

bool click(int,int,unsigned,unsigned)
{
	printf("That was a click!\n");
}

bool drag(int,int,int,int,unsigned)
{
	printf("That was a drag!\n");
}

bool key_down(unsigned key, unsigned mods)
{
	printf("::key_down(0x%06x,0x%06x)==%s -- %d keys are now down\n", key, mods,
		fb->keyname(key, mods, false).c_str(),
		fb->num_keys_down());

	return true;
}

bool key_up(unsigned key, unsigned press_mods, unsigned release_mods)
{
	printf("::key_up(0x%06x,0x%06x,0x%06x)==%s -- %d keys are now down\n", key, press_mods, release_mods,
		fb->keyname(key, release_mods, false).c_str(),
		fb->num_keys_down());

	// Quit when they let up on Q or escape.
	if( (key == 'q') || (key == 'Q') || (key == keyboard_input::KEY_escape) )
	{
		fb->quit_window();
	}

	return true;
}


int main(int argc, char** argv)
{
	x_shift = y_shift = 0;
	Gtk::Main kit(argc, argv);

	fb = new gtkmm_input_window;

	fb->mouse_moved.connect(sigc::ptr_fun(&mouse_moved));
	fb->mouse_clicked.connect(sigc::ptr_fun(&click));
	fb->mouse_dragged.connect(sigc::ptr_fun(&drag));
	fb->buffer_update.connect(sigc::ptr_fun(&update));
	fb->key_pressed.connect(sigc::ptr_fun(&key_down));
	fb->key_released.connect(sigc::ptr_fun(&key_up));

	fb->add_modifier_ignore_mask(keyboard_input::keyboard_numlock);

	fb->disable_repeat();

	//  barf = xpm_convert_image<unsigned char,bool>(barf_xpm);
	//   barf = xpm_convert_image<unsigned char,bool>(wheelbarrow_xpm);
	barf = xpm_convert_image<unsigned char,bool>(al_xpm);
	barf = scale_image(barf, 8);

	printf("Creating a rectangle...\n"); fflush(stdout);
	rectangle<unsigned> r(barf.get_width() / 4,
		barf.get_width() - (barf.get_width() / 4),
		barf.get_height() / 4,
		barf.get_height() - (barf.get_height() / 4));

	printf("Trying to sub an image using a rectangle...\n");  fflush(stdout);
	barf = barf.sub_image(r);

	fb->run_window();

	delete fb;

	return 0;
}
