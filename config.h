/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
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
         *        WM_CLASS(STRING) = instance, class
         *        WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "grid.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[]=",      tile },    /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
	    { "###",      grid },
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
static const char *termcmd[]  = { "st",  "-e", "/bin/fish", NULL };

static Key keys[] = {
    /* modifier                     key                function        argument */
    { MODKEY,                       XK_q,              killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,              spawn,          SHCMD("dmenusysact") },
    { MODKEY,                       XK_w,              spawn,          SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,             XK_w,              NULL,           {0} },
    { MODKEY,                       XK_f,              setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,             XK_f,              NULL,           {0} },
    { MODKEY,                       XK_p,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_p,              NULL,           {0} },
    { MODKEY,                       XK_g,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_g,              NULL,           {0} },
    { MODKEY,                       XK_j,              focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_j,              tagmon,         {.i = +1 } },
    { MODKEY,                       XK_l,              focusstack,     {.i = INC(-1) } },
    { MODKEY|ShiftMask,             XK_l,              pushstack,      {.i = INC(-1) } },
    { MODKEY,                       XK_u,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_u,              NULL,           {0} },
    { MODKEY,                       XK_y,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_y,              NULL,           {0} },

    { MODKEY,                       XK_a,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_a,              NULL,           {0} },
    { MODKEY,                       XK_r,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_r,              NULL,           {0} },
    { MODKEY,                       XK_s,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_s,              NULL,           {0} },
    { MODKEY,                       XK_t,              setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,             XK_t,              NULL,           {0} },
    { MODKEY,                       XK_d,              spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_d,              NULL,           {0} },
    { MODKEY,                       XK_h,              focusstack,     {.i = INC(+1) } }, 
    { MODKEY|ShiftMask,             XK_h,              pushstack,      {.i = INC(+1) } },
    { MODKEY,                       XK_n,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_n,              NULL,           {0} },
    { MODKEY,                       XK_e,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_e,              NULL,           {0} },
    { MODKEY,                       XK_i,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_i,              NULL,           {0} },
    { MODKEY,                       XK_o,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_o,              NULL,           {0} },

    { MODKEY,                       XK_z,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_z,              NULL,           {0} },
    { MODKEY,                       XK_x,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_x,              NULL,           {0} },
    { MODKEY,                       XK_c,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_c,              NULL,           {0} },
    { MODKEY,                       XK_v,              NULL,           {0} },
    { MODKEY|ShiftMask,             XK_v,              NULL,           {0} },
    { MODKEY,                       XK_b,              togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_b,              NULL,           {0} },
    { MODKEY,                       XK_k,              focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_k,              tagmon,         {.i = -1 } },
    { MODKEY,                       XK_m,              setlayout,      {.v = &layouts[2]} },
    { MODKEY|ShiftMask,             XK_m,              NULL,           {0} },

    { MODKEY,                       XK_0,              showgrid,       {0} },
    { MODKEY|ShiftMask,             XK_0,              tag,            {.ui = ~0 } },

      TAGKEYS(                      XK_1,                              0)
      TAGKEYS(                      XK_2,                              1)
      TAGKEYS(                      XK_3,                              2)
      TAGKEYS(                      XK_4,                              3)
      TAGKEYS(                      XK_5,                              4)
      TAGKEYS(                      XK_6,                              5)
      TAGKEYS(                      XK_7,                              6)
      TAGKEYS(                      XK_8,                              7)
      TAGKEYS(                      XK_9,                              8)

    { MODKEY,                       XK_Return,         spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_Return,         NULL,           {0} },
    { MODKEY,                       XK_space,          zoom,           {0} },
    { MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
    { MODKEY,                       XK_Tab,            view,           {0} },
    { MODKEY,                       XK_comma,          NULL,           {0} },
    { MODKEY|ShiftMask,             XK_comma,          NULL,           {0} },
    { MODKEY,                       XK_period,         NULL,           {0} },
    { MODKEY|ShiftMask,             XK_period,         NULL,           {0} },

    { MODKEY,                       XK_Left,           setmfact,       {.f = -0.01 } },
    { MODKEY,                       XK_Right,          setmfact,       {.f = +0.01 } },
    { MODKEY,                       XK_Page_Up,        NULL,           {0} },
    { MODKEY|ShiftMask,             XK_Page_Up,        NULL,           {0} },
    { MODKEY,                       XK_Page_Down,      NULL,           {0} },
    { MODKEY|ShiftMask,             XK_Page_Down,      NULL,           {0} },

    { MODKEY,                       XK_Insert,         NULL,           {0} },
    { MODKEY|ShiftMask,             XK_Insert,         NULL,           {0} },
    { 0,                            XK_Print,          spawn,          SHCMD("") },
    { ShiftMask,                    XK_Print,          spawn,          SHCMD("") },
    { MODKEY,                       XK_Print,          spawn,          SHCMD("dmenurecord") },
    { MODKEY|ShiftMask,             XK_Print,          spawn,          SHCMD("dmenurecord kill") },
    { MODKEY,                       XK_Delete,         spawn,          SHCMD("dmenurecord kill") },
    { MODKEY,                       XK_BackSpace,      spawn,          SHCMD("dmenusysact") },
    { MODKEY,                       XK_Scroll_Lock,    spawn,          SHCMD("") },

    { MODKEY,                       XK_F1,             NULL,           {0} },
    { MODKEY,                       XK_F2,             NULL,           {0} },
    { MODKEY,                       XK_F3,             NULL,           {0} },
    { MODKEY,                       XK_F4,             NULL,           {0} },
    { MODKEY,                       XK_F5,             NULL,           {0} },
    { MODKEY,                       XK_F6,             NULL,           {0} },
    { MODKEY,                       XK_F7,             NULL,           {0} },
    { MODKEY,                       XK_F8,             NULL,           {0} },
    { MODKEY,                       XK_F9,             NULL,           {0} },
    { MODKEY,                       XK_F10,            NULL,           {0} },
    { MODKEY,                       XK_F11,            NULL,           {0} },
    { MODKEY,                       XK_F12,            NULL,           {0} },
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

