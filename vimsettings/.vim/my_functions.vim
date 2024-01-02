function! Comment()
	let ft = &filetype
	if ft == 'php' || ft == 'ruby' || ft == 'sh' || ft == 'make' || ft == 'python' || ft == 'perl'
		silent s/^/\# /
	elseif ft == 'javascript' || ft == 'c' || ft == 'cpp' || ft == 'java' || ft == 'objc' || ft == 'scala' || ft == 'go'
		silent s:^:\/\/ :g
	elseif ft == 'vim'
		silent s:^:\" :g
"
" add more filetypes here..
"
	else
		silent s:^:\# :g
	endif
endfunction

function! Uncomment()
	let ft = &filetype
	if ft == 'php' || ft == 'ruby' || ft == 'sh' || ft == 'make' || ft == 'python' || ft == 'perl'
		silent s/^\# //
	elseif ft == 'javascript' || ft == 'c' || ft == 'cpp' || ft == 'java' ||ft == 'objc' || ft == 'scala' || ft == 'go'
		silent s:^\/\/ ::g
	elseif ft == 'vim'
		silent s:^\" ::g
"
" add more filetypes here..
"
	else
		silent s:^\# ::g
	endif
endfunction

function! Togglecomment()
	try
		call Uncomment()
	catch
		call Comment()
	endtry
endfunction


" Sadece Insert modundayken whitespace karakterleri gostermek icin
" function! ShowHiddenChars()
" 	set list
" endfunction
" 
" function! HideHiddenChars()
" 	set nolist
" endfunction

autocmd InsertEnter * call ShowHiddenChars()
autocmd InsertLeave * call HideHiddenChars()
