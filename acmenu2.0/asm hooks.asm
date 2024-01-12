section .rodata
  scale: dd 100.0
  empty: dd 0

section .data
  global _SpreadScale
  global _RecoilScale
  global _PushScale
  global _InfAmmo
  global _InfReserves
  global _firerate
  global _reload
  global _godmode
  global _ArmorPiercing

  extern _player
  extern _config

  struc entity
      .pad_0000:      resd 59
      .health:        resd 1
      .pad_031C:      resd 157
      .weapon_class:  resd 1
  endstruc

  struc weapon
      .padding:    resd 6
      .delay_ptr:  resd 1
  endstruc

  struc cfg
      .padding:      resd 3
      .recoil:       resd 1
      .spread:       resd 1
      ._push:        resd 1
      .firerate:     resd 1
      .ReloadSpeed:  resd 1
      .padding_2:    resw 5
      .shooting:     resb 1
  endstruc

section .text
  _SpreadScale:
      call [eax+4]
      mov ecx, [_player]
      cmp ecx, [esp+4]
      jne .exit
      movss xmm0, [_config + cfg.spread]
      divss xmm0, [scale]
      movd xmm1, eax
      cvtdq2ps xmm1, xmm1
      mulss xmm1, xmm0
      cvttss2si eax, xmm1
    .exit:
      mov edx, [edi]
      ret
  _RecoilScale:
      cmp [_player], edi
      jne .exit
      movss xmm3, [_config + cfg.recoil]
      divss xmm3, [scale]
      mulss xmm2, xmm3
      mulss xmm0, xmm3
    .exit:
      minss xmm2, xmm0
      movss [eax+0x40], xmm2
      add esp, 0x28
      ret 8
  _InfAmmo:
      cmp edi, [_player]
      je .exit
      dec dword [eax]
    .exit:
      lea eax, [esp+0x1C]
      ret
  _InfReserves:
      mov ecx, [_player]
      cmp [ecx + entity.weapon_class], edi
      je .exit
      sub [eax], esi
    .exit:
      mov eax, [edi+0xC]
      ret
  _firerate:
      cmp edi, [_player]
      jne .exit
      mov ecx, 20
      movd xmm1, ecx
      cvtdq2ps xmm1, xmm1
      mov ecx, [_config]
      movss xmm0, [ecx + cfg.firerate]
      mulss xmm0, xmm1
      cvttss2si ecx, xmm0
    .exit:
      mov [eax], ecx
      mov eax, [esi+0x14]
      ret
  _reload:
      mov edx, [_player]
      mov edx, [edx + entity.weapon_class]
      cmp ecx, [edx + weapon.delay_ptr]
      jne .exit
      movss xmm0, [_config + cfg.ReloadSpeed]
      movd xmm1, [scale]
      cvtdq2ps xmm1, xmm1
      movss xmm2, xmm1
      subss xmm1, xmm0
      divss xmm1, xmm2
      movd xmm0, eax
      cvtdq2ps xmm0, xmm0
      mulss xmm0, xmm1
      cvttss2si eax, xmm0
    .exit:
      add [ecx], eax
      mov eax, [edi+0x10]
      ret
  _godmode:
      add ebx, 4
      mov eax, [_player]
      add eax, entity.health
      cmp ebx, eax
      cmove esi, [empty]
      sub [ebx], esi
      mov eax, esi
      ret
  _ArmorPiercing:
      cvttss2si ecx, xmm1
      cmp edi, [_player]
      cmove ecx, [empty]
      sub esi, ecx
      ret
  _PushScale:
      mov eax, [_player]
      cmp eax, [esp+4]
      je .main
      jmp [edx+8] ;Intended VF call
    .main:
      mov eax, [ecx+0xC]
      movsx eax, word [eax+0x54]
      movd xmm1, eax
      cvtdq2ps xmm1, xmm1 ;base push value
      movss xmm0, [_config + cfg._push]
      divss xmm0, [scale]
      mulss xmm1, xmm0
      movd eax, xmm1 
      push eax
      fld dword [esp]
      pop eax
      ret