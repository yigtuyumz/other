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
set tabstop=4
set mouse=a
colorscheme codedark
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
nnoremap <silent> <F11> :resize +999<CR>:vertical resize +999<CR>
inoremap <silent> <F11> <ESC>:resize +999<CR>:vertical resize +999<CR>
vnoremap <silent> <F11> :resize +999<CR>:vertical resize +999<CR>
"""""""""""""""""""""""""""""""""""""""""


"""""""""""""""""""42""""""""""""""""""""
map <F12> :Stdheader<CR>
"""""""""""""""""""""""""""""""""""""""""


""""""""""""YORUM SATIRI YAP"""""""""""""
nnoremap <silent> <C-k><C-k> :call ToggleComment()<CR>
inoremap <silent> <C-k><C-k> <ESC> :call ToggleComment()<CR>
vnoremap <silent> <C-k><C-k> :call ToggleComment()<CR>
"""""""""""""""""""""""""""""""""""""""""


""""""""""""""TAB AYARLARI"""""""""""""""
nnoremap <silent> <C-t> :tabnew<CR>
" previous	tab		<C-PageUp>
" next		tab		<C-PageDown>
" close		tab		<C-w><C-q>
map <C-Up> :tabnext<CR>
map <C-Down> :tabprev<CR>
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


""""""""""""""FILE EXPLORER""""""""""""""
let g:netrw_banner=0
let g:netrw_browse_split=4
let g:netrw_winsize=15
let g:netrw_altv=1
let g:netrw_alto= 1

map <silent> <C-E> :Lexplore<CR>
"""""""""""""""""""""""""""""""""""""""""
