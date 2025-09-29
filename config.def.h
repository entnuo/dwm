/* See LICENSE file for copyright and license details. */

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 		= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 		= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 		= 400;	/* tab menu width */
static const unsigned int maxHTab 		= 100;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Unifont:size=10:antialias=true:autohint=true",
                                        "monospace:size=10:antialias=true:autohint=true",
                                        "Noto Color Emoji:size=10:antialias=true:autohint=true",
                                        "waffle:size=14:antialias=true:autohint=true" };
//static const char *fonts[]          = { "Noto Sans Mono CJK JP:size=10:antialias=true","Noto Color Emoji:size=10","monospace:size=10","waffle:size=10" };


static const char col_white[]       = "#ffffff";
static const char col_grayb[]       = "#343434";
static const char col_black[]       = "#191919";
static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm]   = { col_white, col_black, col_grayb },
	[SchemeSel]    = { col_black, col_white, col_white },
	[SchemeTitle]  = { col_white, col_black, col_black },
};

static const char *const autostart[] = {
        "aslstatus", NULL,
        "sh", "-c", "fcitx5 || fcitx", NULL,
        "sh", "-c", "${HOME}/.scripts/fehbg", NULL,
        "sh", "-c", "${HOME}/.scripts/welcome", NULL,
        //"sh", "-c", "pgrep -x redshift > /dev/null || redshift", NULL,
        "sh", "-c", "sleep 2 && pgrep -x sxhkd > /dev/null || sxhkd", NULL, // a small delay so sxhkd wont take dwm keybinds
	NULL /* terminate */
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "一", "二", "ゲーム", "勉強", "音楽" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance       title               tags mask     isfloating   monitor */
	{ "Ardour",      NULL,       NULL,                  0,            0,           -1 },
	{ "firefox",     NULL,       NULL,                  1 << 0,       0,           -1 },
	{ NULL,          NULL,       "Picture-in-Picture",  ~0,           1,           -1 },
	{ "discord",     NULL,       NULL,                  1 << 1,       0,           -1 },
	{ NULL,          NULL,       "Steam",               1 << 2,       0,           -1 },
	{ "steam",       NULL,       "Steam",               1 << 2,       0,           -1 },
	{ "steam",       NULL,       "Special Offers",      1 << 2,       1,           -1 },
	{ "steam",       NULL,       "Steam - Browser",     1 << 2,       1,           -1 },
	{ "Lutris",      NULL,       NULL,                  1 << 2,       0,           -1 },
	{ "Lutris",      NULL,       "Add games to Lutris", 1 << 2,       1,           -1 },
	{ "Anki",        NULL,       NULL,                  1 << 3,       1,           -1 },
	{ "Pavucontrol", NULL,       NULL,                  1 << 4,       0,           -1 },
	{ "pavucontrol", NULL,       NULL,                  1 << 4,       0,           -1 },
	{ "Gimp",        NULL,       NULL,                  0,            0,           -1 },
	{ "keepassxc",   NULL,       NULL,                  0,            1,           -1 },
	{ "mpv",         NULL,       NULL,                  0,            1,           -1 },
	{ "Nsxiv",       NULL,       NULL,                  0,            1,           -1 },
	{ "MEGAsync",    NULL,       NULL,                  0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[堅い]",      tile },    /* first entry is default */
	{ "[浮く]",      NULL },    /* no layout function means floating behavior */
	{ "[中心]",      monocle },
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
static const char *dmenucmd[] = { "sh", "-c", "dmenu_run_history || dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefoxcmd[]  = { "firefox", NULL };
static const char *firefoxPrivatecmd[]  = { "firefox", "--private-window", NULL };
static const char *screenshotSelect[]  = { "scrot", "-s", 
                                         "-e",
                                         "'xclip -selection clipboard -t image/png $f && notify-send \"Screenshot: $f taken\"'", 
                                         NULL };
static const char *screenshotScreen[]  = { "scrot", "-e",
                                         "'xclip -selection clipboard -t image/png $f && notify-send \"Screenshot: $f taken\"'",
                                         NULL };

static const Key keys[] = {
	/* modifier                     key                   function        argument */
	{ MODKEY,                       XK_Return,            spawn,          {.v = termcmd } },
    { MODKEY,                       XK_w,                 spawn,          {.v = firefoxcmd} },
    { MODKEY|ShiftMask,             XK_w,                 spawn,          {.v = firefoxPrivatecmd} },
	{ MODKEY,                       XK_n,                 spawn,          SHCMD("st nnn -HDd -T c") },
	{ MODKEY|ShiftMask,             XK_x,                 spawn,          SHCMD("slock") },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_q,                 spawn,          SHCMD("killall -p dwm") },

    // scripts
    // NOTE: 0 in MODKEY means no MODKEY (NULL gives compiler time warning)
    // TODO: organize this section of code for easy modification
	{ MODKEY|ShiftMask,             XK_e,                      spawn,          {.v = dmenucmd } }, // dmenu with cache
	{ MODKEY,                       XK_f,                      spawn,          SHCMD("$HOME/.scripts/sdfl") }, // simple dmenu file "manager" idk
    { MODKEY|ShiftMask,             XK_g,                      spawn,          {.v = (const char*[]){ "powermenu", NULL } } },
    { 0,                            XK_F1,                     spawn,          {.v = (const char*[]){ "volume", "tog", NULL } } }, // mute volume
    { 0,                            XF86XK_AudioMute,          spawn,          {.v = (const char*[]){ "volume", "tog", NULL } } }, // mute volume
    { 0,                            XK_F2,                     spawn,          {.v = (const char*[]){ "volume", "dec", NULL } } }, // dec volume by 2
    { 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = (const char*[]){ "volume", "dec", NULL } } }, // dec volume by 2
    { 0,                            XK_F3,                     spawn,          {.v = (const char*[]){ "volume", "inc", NULL } } }, // inc volume by 2
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = (const char*[]){ "volume", "inc", NULL } } }, // inc volume by 2
    { MODKEY,                       XK_F2,                     spawn,          {.v = (const char*[]){ "volume", "sdec", NULL } } }, // dec volume by 5
    { MODKEY,                       XF86XK_AudioLowerVolume,   spawn,          {.v = (const char*[]){ "volume", "sdec", NULL } } }, // dec volume by 5
    { MODKEY,                       XK_F3,                     spawn,          {.v = (const char*[]){ "volume", "sinc", NULL } } }, // inc volume by 5
    { MODKEY,                       XF86XK_AudioRaiseVolume,   spawn,          {.v = (const char*[]){ "volume", "sinc", NULL } } }, // inc volume by 5
    { MODKEY|ShiftMask,             XK_F3,                     spawn,          {.v = (const char*[]){ "volume", "abovemax", NULL } } }, // inc volume above 100
    { MODKEY|ShiftMask,             XF86XK_AudioRaiseVolume,   spawn,          {.v = (const char*[]){ "volume", "abovemax", NULL } } }, // inc volume above 100
    { 0,                            XK_F11,                    spawn,          {.v = (const char*[]){ "luz", "dec", NULL } } }, // dec brightness by 1
    { 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = (const char*[]){ "luz", "dec", NULL } } }, // dec brightness by 1
    { 0,                            XK_F12,                    spawn,          {.v = (const char*[]){ "luz", "inc", NULL } } }, // inc brightness by 1
    { 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = (const char*[]){ "luz", "inc", NULL } } }, // inc brightness by 1
    { MODKEY,                       XK_F11,                    spawn,          {.v = (const char*[]){ "luz", "sdec", NULL } } }, // dec brightness by 5
    { MODKEY,                       XF86XK_MonBrightnessDown,  spawn,          {.v = (const char*[]){ "luz", "sdec", NULL } } }, // dec brightness by 5
    { MODKEY,                       XK_F12,                    spawn,          {.v = (const char*[]){ "luz", "sinc", NULL } } }, // inc brightness by 5
    { MODKEY,                       XF86XK_MonBrightnessUp,    spawn,          {.v = (const char*[]){ "luz", "sinc", NULL } } }, // inc brightness by 5
    { 0,                            XK_Print,                  spawn,          {.v = screenshotSelect } },
    { MODKEY,                       XK_Print,                  spawn,          {.v = screenshotScreen } },
    { MODKEY|ShiftMask,             XK_k,                      spawn,          {.v = (const char*[]){ "killprocess", NULL } } },


	{ MODKEY,                       XK_b,                 togglebar,      {0} },
	{ MODKEY,                       XK_j,                 focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                 focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                 incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                 incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                 setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                 setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,            zoom,           {0} },
	{ MODKEY,                       XK_q,	              view,           {0} },
	{ MODKEY,                       XK_Escape,            killclient,     {0} },
	{ Mod1Mask,                     XK_F4,                killclient,     {0} },
	{ MODKEY,                       XK_t,                 setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_s,                 setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                 setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,             setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,             togglefloating, {0} },
	{ MODKEY,                       XK_0,                 view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                 tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,             focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,            focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,             tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,            tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,             setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,             setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_equal,             setgaps,        {.i = +1 } },
	{ Mod1Mask,              		XK_Tab,               altTabStart,    {0} },
	{ MODKEY,                       XK_bracketright,      shiftview,      { .i = +1 } },
	{ MODKEY,                       XK_bracketleft,       shiftview,      { .i = -1 } },
	{ MODKEY|Mod1Mask,              XK_q,                 quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

