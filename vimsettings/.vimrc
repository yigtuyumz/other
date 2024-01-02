"""""""""""""GENEL AYARLAR"""""""""""""""
syntax on
filetype plugin indent on
set backspace=2
set incsearch
set ruler
set rulerformat=[%v][%l]
set number
set relativenumber
set cinoptions=l1
set cindent
" colorscheme solarized
"""""""""""""""""""""""""""""""""""""""""


"""""SECILI ELEMANLARI KAYDIR""""""""""""
nnoremap <silent> <F3> :m .+1<CR>==
nnoremap <silent> <F2> :m .-2<CR>==

inoremap <silent> <F3> <Esc>:m .+1<CR>==
inoremap <silent> <F2> <Esc>:m .-2<CR>==

vnoremap <silent> <F3> :m '>+1<CR>gv=gv
vnoremap <silent> <F2> :m '<-2<CR>gv=gv
"""""""""""""""""""""""""""""""""""""""""

"""DOSYA UZANTILARINA GORE TAB AYARLARI""
" au FileType c setlocal tabstop=4 shiftwidth=4 noexpandtab autoindent
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

""""""""""""""TAB AYARLARI"""""""""""""""
nnoremap <silent> <C-t> :tabnew<CR>
" previous	tab		<C-PageUp>
" next		tab		<C-PageDown>
" close		tab		<C-w><C-q>
map <C-Up> :tabnext<CR>
map <C-Down> :tabprev<CR>
"""""""""""""""""""""""""""""""""""""""""

"""""""""""""""""""42""""""""""""""""""""
map <C-F12> :Stdheader<CR>
"""""""""""""""""""""""""""""""""""""""""


""""WHITESPACE KARAKTERLERI GOSTERME"""""
" set listchars=eol:↓,tab:\ \ ┊,trail:●,extends:…,precedes:…,space:·
"""""""""""""""""""""""""""""""""""""""""


"""""""""""""GORSEL EFEKTLER"""""""""""""
set fillchars=vert:\│
highlight VertSplit cterm=none gui=none
"""""""""""""""""""""""""""""""""""""""""

""" Vim paketlerini yukler"""""""""""""""
packloadall
"""""""""""""""""""""""""""""""""""""""""


""" C kutuphanesi icin ekstra path"""""""
set path+=/usr/lib/gcc/x86_64-linux-gnu/9/include
"""""""""""""""""""""""""""""""""""""""""

