"----------------------------------------------------------------------------------------------------------------------------------------------------
"
" Vim syntax file
"
" Language:        Temizer Photo Collage
" Maintainer:      Selim Temizer
" Creation:        September 15, 2021
" Latest Revision: September 15, 2021
" Note:            Syntax coloring may not work well if comments come between command tokens
"
"----------------------------------------------------------------------------------------------------------------------------------------------------

if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif

"----------------------------------------------------------------------------------------------------------------------------------------------------

syn keyword tpcTodo        TODO NOTE                                                         contained
syn keyword tpcTodo        FIXME XXX                                                         contained

syn match   tpcComment     '#.*$'        contains=tpcTodo

syn keyword tpcStatement   Output        nextgroup=tpcOutputFile  skipwhite skipnl skipempty
syn match   tpcOutputFile  '\"[^"]*\"'   nextgroup=tpcWidth       skipwhite skipnl skipempty contained
syn match   tpcWidth       '\d\+'        nextgroup=tpcHeight      skipwhite skipnl skipempty contained
syn match   tpcHeight      '\d\+'        nextgroup=tpcMaxValue    skipwhite skipnl skipempty contained
syn match   tpcMaxValue    '\d\+'        nextgroup=tpcRed         skipwhite skipnl skipempty contained
syn match   tpcRed         '\d\+'        nextgroup=tpcGreen       skipwhite skipnl skipempty contained
syn match   tpcGreen       '\d\+'        nextgroup=tpcBlue        skipwhite skipnl skipempty contained
syn match   tpcBlue        '\d\+'        display                                             contained

syn keyword tpcStatement   Read          nextgroup=tpcInputFile   skipwhite skipnl skipempty
syn match   tpcInputFile   '\"[^"]*\"'   display                                             contained

syn keyword tpcStatement   Translate     nextgroup=tpcX           skipwhite skipnl skipempty
syn keyword tpcStatement   Scale         nextgroup=tpcX           skipwhite skipnl skipempty
syn keyword tpcStatement   Shear         nextgroup=tpcX           skipwhite skipnl skipempty
syn match   tpcX           '[.\-0-9]\+'  nextgroup=tpcY           skipwhite skipnl skipempty contained "Something matching a number
syn match   tpcY           '[.\-0-9]\+'  display                                             contained "Something matching a number

syn keyword tpcStatement   Rotate        nextgroup=tpcAngle       skipwhite skipnl skipempty
syn match   tpcAngle       '[.\-0-9]\+'  display                                             contained "Something matching a number

syn keyword tpcStatement   Copy
syn keyword tpcStatement   Reset

"----------------------------------------------------------------------------------------------------------------------------------------------------

let b:current_syntax = "tpc"

"----------------------------------------------------------------------------------------------------------------------------------------------------

" Xterm colors - Cheat Sheet:  https://jonasjacek.github.io/colors/

highlight tpcOutputFile ctermfg=124 guifg=#af0000
highlight tpcInputFile  ctermfg=28  guifg=#008700

highlight tpcWidth      ctermfg=32  guifg=#0087d7 cterm=reverse   gui=reverse
highlight tpcHeight     ctermfg=166 guifg=#d75f00 cterm=reverse   gui=reverse
highlight tpcMaxValue   ctermfg=248 guifg=#a8a8a8 cterm=reverse   gui=reverse

highlight tpcRed        ctermfg=160 guifg=#d70000
highlight tpcGreen      ctermfg=40  guifg=#00d700
highlight tpcBlue       ctermfg=111 guifg=#87afff

highlight tpcX          ctermfg=32  guifg=#0087d7
highlight tpcY          ctermfg=166 guifg=#d75f00

highlight tpcAngle      ctermfg=13  guifg=#ff00ff

"----------------------------------------------------------------------------------------------------------------------------------------------------

hi def link tpcTodo      Todo
hi def link tpcComment   Comment
hi def link tpcStatement Statement

" Some Possible Choices:
"-----------------------
" Comment     // Blue
" PreProc     // Purple
" Type        // Green
" Constant    // Red
" Statement   // Yellow
" Identifier  // Cyan
" Special     // Orange
" Underlined  // Blue, underlined
" Todo        // Yellow background
" Error       // Dark Red
" Ignore      // (Invisible)

"----------------------------------------------------------------------------------------------------------------------------------------------------
