"""""""""""""GENEL AYARLAR"""""""""""""""
source ~/.vim/my_functions.vim      " imports vimscript
set tabstop=4                       " sets tab width
set textwidth=80                    " set line width to 80 characters
set nolist                          " disable list view
set nohlsearch                      " disable search highlight
set nonumber                        " disable line numbers
set encoding=utf-8                  " for special characters in turkish language
set nolinebreak                     " for disabling auto newline
set nowrap                          " for disabling auto newline
set number                          " for displaying line numbers
set fo-=t                           " preventing auto-insert newline at EOL
"""""""""""""""""""""""""""""""""""""""""


"""""SECILI ELEMANLARI KAYDIR""""""""""""
nnoremap <silent> <F3> :m .+1<CR>==
nnoremap <silent> <F2> :m .-2<CR>==

inoremap <silent> <F3> <Esc>:m .+1<CR>==
inoremap <silent> <F2> <Esc>:m .-2<CR>==

vnoremap <silent> <F3> :m '>+1<CR>gv=gv
vnoremap <silent> <F2> :m '<-2<CR>gv=gv
"""""""""""""""""""""""""""""""""""""""""


""""""""""AKTIF SPLIT TAM EKRAN""""""""""
nnoremap <silent> <C-F11> :resize +999<CR>:vertical resize +999<CR>
inoremap <silent> <C-F11> <ESC>:resize +999<CR>:vertical resize +999<CR>
vnoremap <silent> <C-F11> :resize +999<CR>:vertical resize +999<CR>
"""""""""""""""""""""""""""""""""""""""""


""""""""""""YORUM SATIRI YAP"""""""""""""
nnoremap <silent> <C-k><C-k> :call Togglecomment()<CR>
inoremap <silent> <C-k><C-k> <ESC> :call Togglecomment()<CR>
vnoremap <silent> <C-k><C-k> :call Togglecomment()<CR>
"""""""""""""""""""""""""""""""""""""""""

""""""FIREFOX BENZERI TAB KULLANIMI""""""
nnoremap <silent> <C-t> :tabnew<CR>
" previous	tab		<C-PageUp>
" next		tab		<C-PageDown>
" close		tab		<C-w><C-q>
"""""""""""""""""""""""""""""""""""""""""

"""DOSYA UZANTILARINA GORE TAB AYARLARI""
" au FileType sh set tabstop=4 shiftwidth=4 softtabstop=4 expandtab autoindent
" au FileType c set tabstop=4 shiftwidth=4 softtabstop=4 noexpandtab autoindent
au FileType sh setlocal tabstop=4 shiftwidth=4 noexpandtab autoindent
au FileType c setlocal tabstop=4 shiftwidth=4 noexpandtab autoindent
au FileType js setlocal tabstop=4 shiftwidth=4 noexpandtab autoindent

"""""""""""""""""""""""""""""""""""""""""


"""""""""WHITESPACE RENKLENDIRME"""""""""
highlight ExtraWhitespace ctermbg=darkred guibg=darkred
match ExtraWhitespace '\s\+$'
"""""""""""""""""""""""""""""""""""""""""

""""""""80 KARAKTER+ RENKLENDIRME""""""""
highlight OverLengthCharacters ctermbg=darkgrey guibg=darkgrey ctermfg=white guifg=white
2match OverLengthCharacters '\%>80v.\+'
"""""""""""""""""""""""""""""""""""""""""

		" IKISI BIRDEN TEK REGEX
		" highlight ExtraCharacters ctermbg=darkred ctermfg=white guibg=darkred guifg=white
		" match ExtraCharacters '\%>80v.\+\|\s\+$'

"""""""""""""""""""42""""""""""""""""""""
map <C-F12> :Stdheader<CR>
"""""""""""""""""""""""""""""""""""""""""

map <C-Up> :tabnext<CR>
map <C-Down> :tabprev<CR>

""""WHITESPACE KARAKTERLERI GOSTERME"""""
set listchars=eol:↓,tab:\ \ ┊,trail:●,extends:…,precedes:…,space:·
"""""""""""""""""""""""""""""""""""""""""


"""""""""""""GORSEL EFEKTLER"""""""""""""
set fillchars=vert:\│
highlight VertSplit cterm=none gui=none
" colorscheme nord
"""""""""""""""""""""""""""""""""""""""""

""" Vim paketlerini yukler"""""""""""""""
packloadall


""" C kutuphanesi icin ekstra path"""""""
set path+=/usr/lib/gcc/x86_64-linux-gnu/9/include


