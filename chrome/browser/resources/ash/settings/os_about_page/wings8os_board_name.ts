// append new board name here

export const Wings8OSBoardNameTitleMap: {[index: string]: string} = {
  'itnt-72': 'itNT 72',
  'itnt-72-go': 'itNT 72 GO',
  'itnt-x': 'itNT X',
  'itnt-80-go': 'itNT 80 GO',
  'link_wings8os': 'Wings8OS Link',
  'samus_wings8os': 'Wings8OS Samus',
  'jerry-wings8os': 'Wings8OS Jerry',
  'fizz-wings8os': 'Wings8rbox',
  'magicbook': 'MagicBook',
  'gpdpocket2': 'GPD Pocket 2',
  'pinebook-pro': 'Pinebook Pro',
  'surface-pro3': 'Surface Pro 3',
  'surface-pro4': 'Surface Pro 4',
  'surface-pro5': 'Surface Pro 5',
  'surface-pro6': 'Surface Pro 6',
  'surface-pro7': 'Surface Pro 7',
  'surface-pro7p': 'Surface Pro 7+',
  'surface-pro8': 'Surface Pro 8',
  'surface-go': 'Surface GO',
  'surface-go2': 'Surface GO 2',
  'surface-go3': 'Surface GO 3',
  'eve_wings8os': 'Pixelbook',
  'kukui_wings8os': 'Wings8tab Duo',
  'one-a1': 'One A1',
  'rpi4-wings8os': 'Raspberry Pi 400',
  'rpi5-wings8os': 'Raspberry Pi 5',
  'orangepi5-wings8os': 'Orange Pi 5',
  'rock5b-wings8os': 'Rock 5B',
  'wings8tab_duo-wings8os': 'Wings8tab Duo',
};

export const Wings8OSBoardNameTitleListWithI18n = [{
  board: 'amd64-wings8os',
  key: 'aboutWings8OSDeviceTitleLegacyIntel',
  fallback: 'Legacy Intel',
}, {
  board: 'amd64-wings8os_iris',
  key: 'aboutWings8OSDeviceTitleModernIntel',
  fallback: 'Modern Intel',
}, {
  board: 'amd64-wings8os_apu',
  key: 'aboutWings8OSDeviceTitleAMDGraphics',
  fallback: 'AMD Graphics',
}, {
  board: 'amd64-wings8os_slim',
  key: 'aboutWings8OSDeviceTitleIntelSlim',
  fallback: 'Intel Slim',
}];

export const Wings8OSBoardNameReleaseNameMap: {[index: string]: string} = {
  'amd64-wings8os': 'for PC',
  'amd64-wings8os_iris': 'for PC',
  'amd64-wings8os_apu': 'for PC',
  'amd64-wings8os_slim': 'for PC',
  'amd64-vmware': 'for VMware',
  'rpi4-wings8os': 'for SBC',
  'rpi5-wings8os': 'for SBC',
  'rock5b-wings8os': 'for SBC',
  'orangepi5-wings8os': 'for SBC',
  'wings8tab_duo-wings8os': '-',
}
