{}:
let
  sources = import ./nix/sources.nix;
  nixpkgs = sources.nixpkgs;
  pkgs = import nixpkgs {};
in
  pkgs.stdenv.mkDerivation rec {
  name = "esp8266-platformio-dev-shell";

  src = builtins.toString ./.;

  buildInputs = with pkgs; [
    esptool
    esptool-ck
    platformio
    gnumake
  ];

  HISTFILE = "${src}/.bash_hist";
  # https://docs.platformio.org/en/latest/envvars.html#directories

  PLATFORMIO_CORE_DIR = "${src}/.platformio";

  shellHook = ''
    echo "Ready!"
  '';
}
