make
bannertool.exe makebanner -i icons-banners/banner.png -a icons-banners/audio.wav -o icons-banners/banner.bnr
bannertool.exe makesmdh -s "Minicraft3DS" -l "3DS Homebrew port of Notch's ludum dare game 'Minicraft', updated." -p "Davideesk/Andre111/ElijahZAwesome" -i icons-banners/icon.png  -o icons-banners/icon.icn
makerom -f cia -o result/Minicraft3DS.cia -DAPP_ENCRYPTED=false -rsf icons-banners/Minicraft3DS.rsf -target t -exefslogo -elf result/Minicraft3DS.elf -icon icons-banners/icon.icn -banner icons-banners/banner.bnr
makerom -f cci -o result/Minicraft3DS.3ds -DAPP_ENCRYPTED=true -rsf icons-banners/Minicraft3DS.rsf -target t -exefslogo -elf result/Minicraft3DS.elf -icon icons-banners/icon.icn -banner icons-banners/banner.bnr
pause