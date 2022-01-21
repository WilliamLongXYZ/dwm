/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Monero",    NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Brave",    NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 8,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "brave-browser-beta", NULL };

static Key keys[] = {
	/* modifier                     key                 function        argument */
	{ MODKEY,                       XK_Escape,          spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Escape,          spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_grave,           spawn,          SHCMD("dmenuunicode") },
	{ MODKEY|ShiftMask,             XK_grave,           spawn,          SHCMD("true") },
	TAGKEYS(                        XK_1,                               0)
	TAGKEYS(                        XK_2,                               1)
	TAGKEYS(                        XK_3,                               2)
	TAGKEYS(                        XK_4,                               3)
	TAGKEYS(                        XK_5,                               4)
	TAGKEYS(                        XK_6,                               5)
	TAGKEYS(                        XK_7,                               6)
	TAGKEYS(                        XK_8,                               7)
	TAGKEYS(                        XK_9,                               8)
	{ MODKEY,                       XK_0,               view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,           spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_minus,           spawn,          SHCMD("true") },
	{ MODKEY,                       XK_equal,           spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_equal,           spawn,          SHCMD("true") },
	{ MODKEY,                       XK_BackSpace,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_BackSpace,       spawn,          SHCMD("true") },

	{ MODKEY,                       XK_Tab,             view,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,             spawn,          SHCMD("true") },
	{ MODKEY,                       XK_q,               killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,               spawn,          SHCMD("sysact") },
	{ MODKEY,                       XK_w,               spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_w,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_e,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_e,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_r,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_r,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_t,               setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_y,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_y,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_u,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_u,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_i,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_i,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_o,               incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,               incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_p,               spawn,          SHCMD("mpc toggle") },
	{ MODKEY|ShiftMask,             XK_p,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_bracketleft,     spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_bracketleft,     spawn,          SHCMD("true") },
	{ MODKEY,                       XK_bracketright,    spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_bracketright,    spawn,          SHCMD("true") },

	{ MODKEY,                       XK_Caps_Lock,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Caps_Lock,       spawn,          SHCMD("true") },
	{ MODKEY,                       XK_a,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_a,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_s,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_s,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_d,               spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_d,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_f,               setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_g,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_g,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_h,               setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_j,               focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_k,               focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_l,               setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_semicolon,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_semicolon,       spawn,          SHCMD("true") },
	{ MODKEY,                       XK_apostrophe,      spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_apostrophe,      spawn,          SHCMD("true") },
	{ MODKEY,                       XK_backslash,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_backslash,       spawn,          SHCMD("true") },
	{ MODKEY,                       XK_Return,          zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Return,          spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_Shift_L,         spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Shift_L,         spawn,          SHCMD("true") },
	{ MODKEY,                       XK_z,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_z,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_x,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_x,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_c,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_c,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_v,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_v,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_b,               togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_n,               spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_n,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_m,               setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_m,               spawn,          SHCMD("true") },
	{ MODKEY,                       XK_comma,           focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_slash,           spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_slash,           spawn,          SHCMD("true") },
	{ MODKEY,                       XK_Shift_R,         spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Shift_R,         spawn,          SHCMD("true") },

	{ MODKEY,                       XK_Control_L,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Control_L,       spawn,          SHCMD("true") },
	{ MODKEY,                       XK_Alt_L,           spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Alt_L,           spawn,          SHCMD("true") },
	{ MODKEY,                       XK_space,           setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,           togglefloating, {0} },
	{ MODKEY,                       XK_Alt_R,           spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Alt_R,           spawn,          SHCMD("true") },
	{ MODKEY,                       XK_Control_R,       spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_Control_R,       spawn,          SHCMD("true") },

	{ MODKEY,                       XK_F1,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F1,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F2,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F2,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F3,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F3,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F4,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F4,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F5,              spawn,          SHCMD("togglewifi") },
	{ MODKEY|ShiftMask,             XK_F5,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F6,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F6,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F7,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F7,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F8,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F8,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F9,              spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F9,              spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F10,             spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F10,             spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F11,             spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F11,             spawn,          SHCMD("true") },
	{ MODKEY,                       XK_F12,             spawn,          SHCMD("true") },
	{ MODKEY|ShiftMask,             XK_F12,             spawn,          SHCMD("true") },

	{ 0,                            XK_Print,           spawn,          SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,                    XK_Print,           spawn,          SHCMD("maimpick") },
	{ MODKEY,                       XK_Print,           spawn,          SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,             XK_Print,           spawn,          SHCMD("dmenurecord kill") },
	{ MODKEY,                       XK_Delete,          spawn,          SHCMD("dmenurecord kill") },
	{ MODKEY,                       XK_Scroll_Lock,     spawn,          SHCMD("killall screenkey || screenkey &") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

