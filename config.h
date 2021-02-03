/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[] = {
    "monospace:size=10",
    "NotoColorEmoji:size=10"
};
static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { "#586e75", "#002b36", "#073642" },
        [SchemeSel]  = { "#93a1a1", "#002b36",  "#586e75" },
};

static const char *const autostart[] = {
        "wallpaper", NULL,
        "remaps", NULL,
        "dwmblocks", NULL,
        "dunst", NULL,
        "unclutter", NULL,
        NULL /* terminate */
};

/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *        WM_CLASS(STRING) = instance, class
         *        WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        /* { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "grid.c"
#include "fibonacci.c"
static const Layout layouts[] = {
        /* symbol     arrange function */
        { "[\\]",       dwindle },  /* first entry is default */
        { "><>",      NULL },    /* no layout function means floating behavior */
        { "[M]",      monocle },
        { "[]=",      tile },  
        { "###",      grid },
        { "[@]",      spiral },
        { NULL,       NULL },
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
#define TERMCMD(cmd) SHCMD("$TERMINAL -e " cmd)

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st",  "-e", "/bin/fish", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", "-e", "/bin/fish", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                                  key                function                 argument */
    { MODKEY,                                    XK_q,              killclient,              {0} },
    { MODKEY|ShiftMask,                          XK_q,              spawn,                   SHCMD("xkill") },
    { MODKEY,                                    XK_w,              spawn,                   SHCMD("$BROWSER") },
    { MODKEY|ShiftMask,                          XK_w,              NULL,                    {0} },
    { MODKEY,                                    XK_f,              togglefullscreen,        {0} },
    { MODKEY|ShiftMask,                          XK_f,              togglefakefullscreen,    {0} },
    { MODKEY,                                    XK_p,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_p,              NULL,                    {0} },
    { MODKEY,                                    XK_g,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_g,              NULL,                    {0} },
    { MODKEY,                                    XK_j,              focusmon,                {.i = +1 } },
    { MODKEY|ShiftMask,                          XK_j,              tagmon,                  {.i = +1 } },
    { MODKEY,                                    XK_l,              focusstack,              {.i = INC(-1) } },
    { MODKEY|ShiftMask,                          XK_l,              pushstack,               {.i = INC(-1) } },
    { MODKEY,                                    XK_u,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_u,              NULL,                    {0} },
    { MODKEY,                                    XK_y,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_y,              NULL,                    {0} },

    { MODKEY,                                    XK_a,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_a,              NULL,                    {0} },
    { MODKEY,                                    XK_r,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_r,              NULL,                    {0} },
    { MODKEY,                                    XK_s,              togglesticky,            {0} },
    { MODKEY|ShiftMask,                          XK_s,              NULL,                    {0} },
    { MODKEY,                                    XK_t,              setlayout,               {.v = &layouts[0]} },
    { MODKEY|ShiftMask,                          XK_t,              NULL,                    {0} },
    { MODKEY,                                    XK_d,              spawn,                   {.v = dmenucmd } },
    { MODKEY|ShiftMask,                          XK_d,              NULL,                    {0} },
    { MODKEY,                                    XK_h,              focusstack,              {.i = INC(+1) } }, 
    { MODKEY|ShiftMask,                          XK_h,              pushstack,               {.i = INC(+1) } },
    { MODKEY,                                    XK_n,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_n,              NULL,                    {0} },
    { MODKEY,                                    XK_e,              setlayout,               {.v = &layouts[1]} },
    { MODKEY|ShiftMask,                          XK_e,              NULL,                    {0} },
    { MODKEY,                                    XK_i,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_i,              NULL,                    {0} },
    { MODKEY,                                    XK_o,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_o,              NULL,                    {0} },

    { MODKEY,                                    XK_z,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_z,              NULL,                    {0} },
    { MODKEY,                                    XK_x,              spawn,                   SHCMD("slock") },
    { MODKEY|ShiftMask,                          XK_x,              spawn,                   SHCMD("slock systemctl suspend") },
    { MODKEY,                                    XK_c,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_c,              NULL,                    {0} },
    { MODKEY,                                    XK_v,              NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_v,              NULL,                    {0} },
    { MODKEY,                                    XK_b,              togglebar,               {0} },
    { MODKEY|ShiftMask,                          XK_b,              NULL,                    {0} },
    { MODKEY,                                    XK_k,              focusmon,                {.i = -1 } },
    { MODKEY|ShiftMask,                          XK_k,              tagmon,                  {.i = -1 } },
    { MODKEY,                                    XK_m,              setlayout,               {.v = &layouts[2]} },
    { MODKEY|ShiftMask,                          XK_m,              spawn,                   SHCMD("volume toggle") },

    { MODKEY,                                    XK_0,              showgrid,                {0} },
    { MODKEY|ShiftMask,                          XK_0,              tag,                     {.ui = ~0 } },

      TAGKEYS(                                   XK_1,                                       0)
      TAGKEYS(                                   XK_2,                                       1)
      TAGKEYS(                                   XK_3,                                       2)
      TAGKEYS(                                   XK_4,                                       3)
      TAGKEYS(                                   XK_5,                                       4)
      TAGKEYS(                                   XK_6,                                       5)
      TAGKEYS(                                   XK_7,                                       6)
      TAGKEYS(                                   XK_8,                                       7)
      TAGKEYS(                                   XK_9,                                       8)

    { MODKEY,                                    XK_Escape,         spawn,                   SHCMD("sysact") },
    { MODKEY|ShiftMask,                          XK_Escape,         NULL,                    {0} },
    { MODKEY,                                    XK_grave,          spawn,                   SHCMD("dmenuemoji") },
    { MODKEY,                                    XK_Return,         spawn,                   {.v = termcmd } },
    { MODKEY|ShiftMask,                          XK_Return,         togglescratch,           {.v = scratchpadcmd } },
    { MODKEY,                                    XK_space,          zoom,                    {0} },
    { MODKEY|ShiftMask,                          XK_space,          togglefloating,          {0} },
    { MODKEY,                                    XK_Tab,            view,                    {0} },
    { MODKEY,                                    XK_comma,          cyclelayout,             {.i = -1 } },
    { MODKEY|ShiftMask,                          XK_comma,          NULL,                    {0} },
    { MODKEY,                                    XK_period,         cyclelayout,             {.i = +1 } },
    { MODKEY|ShiftMask,                          XK_period,         NULL,                    {0} },
    { MODKEY,                                    XK_Left,           setmfact,                {.f = -0.01 } },
    { MODKEY,                                    XK_Right,          setmfact,                {.f = +0.01 } },
    { MODKEY,                                    XK_Page_Up,        NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_Page_Up,        NULL,                    {0} },
    { MODKEY,                                    XK_Page_Down,      NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_Page_Down,      NULL,                    {0} },
    { MODKEY,                                    XK_Insert,         NULL,                    {0} },
    { MODKEY|ShiftMask,                          XK_Insert,         NULL,                    {0} },
    { 0,                                         XK_Print,          spawn,                   SHCMD("maim screenshot-$(date '+%y%m%d-%H%M-%S').png") },
    { ShiftMask,                                 XK_Print,          spawn,                   SHCMD("maim -s | xclip -selection clipboard -t image/png") },
    { ControlMask,                               XK_Print,          spawn,                   SHCMD("maimpick") },
    { MODKEY,                                    XK_Print,          spawn,                   SHCMD("dmenurecord") },
    { MODKEY|ShiftMask,                          XK_Print,          spawn,                   SHCMD("dmenurecord kill") },
    { MODKEY,                                    XK_Delete,         spawn,                   SHCMD("dmenurecord kill") },
    { MODKEY,                                    XK_BackSpace,      spawn,                   SHCMD("sysact") },
    { MODKEY,                                    XK_Scroll_Lock,    spawn,                   SHCMD("") },

    { MODKEY,                                    XK_F1,             NULL,                    {0} },
    { MODKEY,                                    XK_F2,             NULL,                    {0} },
    { MODKEY,                                    XK_F3,             spawn,                   TERMCMD("alsamixer; sigdwmblocks 9") },
    { MODKEY,                                    XK_F4,             NULL,                    {0} },
    { MODKEY,                                    XK_F5,             NULL,                    {0} },
    { MODKEY,                                    XK_F6,             NULL,                    {0} },
    { MODKEY,                                    XK_F7,             NULL,                    {0} },
    { MODKEY,                                    XK_F8,             spawn,                   SHCMD("dmenumount") },
    { MODKEY,                                    XK_F9,             spawn,                   SHCMD("dmenuumount") },
    { MODKEY,                                    XK_F10,            spawn,                   SHCMD("webcam") },
    { MODKEY,                                    XK_F11,            spawn,                   SHCMD("displayselect") },
    { MODKEY,                                    XK_F12,            spawn,                   SHCMD("freeze") },

    { 0, XF86XK_AudioMute,                       spawn,             SHCMD("volume mute") },
    { 0, XF86XK_AudioRaiseVolume,                spawn,             SHCMD("volume up 5") },
    { 0, XF86XK_AudioLowerVolume,                spawn,             SHCMD("volume down 5") },
    { 0, XF86XK_AudioPrev,                       spawn,             SHCMD("mpc prev") },
    { 0, XF86XK_AudioNext,                       spawn,             SHCMD("mpc next") },
    { 0, XF86XK_AudioPause,                      spawn,             SHCMD("mpc pause") },
    { 0, XF86XK_AudioPlay,                       spawn,             SHCMD("mpc play") },
    { 0, XF86XK_AudioStop,                       spawn,             SHCMD("mpc stop") },
    { 0, XF86XK_AudioRewind,                     spawn,             SHCMD("mpc seek -10") },
    { 0, XF86XK_AudioForward,                    spawn,             SHCMD("mpc seek +10") },
    { 0, XF86XK_AudioMedia,                      NULL,              {0} },
    { 0, XF86XK_AudioMicMute,                    NULL,              {0} },
    { 0, XF86XK_PowerOff,                        spawn,             SHCMD("dmenusysact") },
    { 0, XF86XK_Calculator,                      spawn,             TERMCMD("bc -l") },
    { 0, XF86XK_Sleep,                           NULL,              {0} },
    { 0, XF86XK_WWW,                             spawn,             SHCMD("$BROWSER") },
    { 0, XF86XK_DOS,                             spawn,             SHCMD("$TERMINAL") },
    { 0, XF86XK_ScreenSaver,                     NULL,              {0} },
    { 0, XF86XK_TaskPane,                        spawn,             TERMCMD("htop") },
    { 0, XF86XK_Mail,                            NULL,              {0} },
    { 0, XF86XK_MyComputer,                      NULL,              {0} },
    /* { 0, XF86XK_Battery,                      spawn,             SHCMD("") }, */
    { 0, XF86XK_Launch1,                         NULL,              {0} },
    { 0, XF86XK_TouchpadToggle,                  NULL,              {0} },
    { 0, XF86XK_TouchpadOff,                     NULL,              {0} },
    { 0, XF86XK_TouchpadOn,                      NULL,              {0} },
    { 0, XF86XK_MonBrightnessUp,                 spawn,             SHCMD("light -T 1.778") },
    { ControlMask, XF86XK_MonBrightnessUp,       spawn,             SHCMD("sct") },
    { 0, XF86XK_MonBrightnessDown,               spawn,             SHCMD("light -T 0.562") },
    { ControlMask, XF86XK_MonBrightnessDown,     spawn,             SHCMD("sct 4500") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask             button          function        argument */
        { ClkLtSymbol,          0,                     Button1,        cyclelayout,    {.i = 1 } },
        { ClkLtSymbol,          0,                     Button3,        cyclelayout,    {.i = -1 } },
        { ClkWinTitle,          0,                     Button2,        zoom,           {0} },
        { ClkStatusText,        0,                     Button1,        sigdwmblocks,   {.i = 1} },
        { ClkStatusText,        0,                     Button2,        sigdwmblocks,   {.i = 2} },
        { ClkStatusText,        0,                     Button3,        sigdwmblocks,   {.i = 3} },
        { ClkStatusText,        0,                     Button4,        sigdwmblocks,   {.i = 4} },
        { ClkStatusText,        0,                     Button5,        sigdwmblocks,   {.i = 5} },
        { ClkClientWin,         MODKEY,                Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,                Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,                Button3,        resizemouse,    {.i = 0} },
        { ClkClientWin,         MODKEY|ShiftMask,      Button3,        resizemouse,    {.i = 1} },
        { ClkTagBar,            0,                     Button1,        view,           {0} },
        { ClkTagBar,            0,                     Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,                Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,                Button3,        toggletag,      {0} },
};

