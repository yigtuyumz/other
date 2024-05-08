function! ToggleComment()
	let s:comment_map = { 
	\	"c": '\/\/',
	\	"cpp": '\/\/',
	\	"go": '\/\/',
	\	"java": '\/\/',
	\	"javascript": '\/\/',
	\	"lua": '--',
	\	"scala": '\/\/',
	\	"php": '\/\/',
	\	"python": '#',
	\	"ruby": '#',
	\	"rust": '\/\/',
	\	"sh": '#',
	\	"desktop": '#',
	\	"fstab": '#',
	\	"conf": '#',
	\	"profile": '#',
	\	"bashrc": '#',
	\	"bash_profile": '#',
	\	"mail": '>',
	\	"eml": '>',
	\	"bat": 'REM',
	\	"ahk": ';',
	\	"vim": '"',
	\	"tex": '%',
	\ }
	if has_key(s:comment_map, &filetype)
		let comment_leader = s:comment_map[&filetype]
		if getline('.') =~ "^\\s*" . comment_leader . " " 
			" Uncomment the line
			execute "silent s/^\\(\\s*\\)" . comment_leader . " /\\1/"
		else 
			if getline('.') =~ "^\\s*" . comment_leader
				" Uncomment the line
				execute "silent s/^\\(\\s*\\)" . comment_leader . "/\\1/"
			else
				" Comment the line
				execute "silent s/^\\(\\s*\\)/\\1" . comment_leader . " /"
			end
		end
	else
		echo "No comment leader found for filetype"
	end
endfunction

" Sadece Insert modundayken whitespace karakterleri gostermek icin
function! ShowHiddenChars()
	set list
	set listchars=eol:↓,tab:\ \ ┊,trail:●,extends:…,precedes:…,space:·

endfunction

function! HideHiddenChars()
	set nolist
endfunction
 
autocmd InsertEnter * call ShowHiddenChars()
autocmd InsertLeave * call HideHiddenChars()

