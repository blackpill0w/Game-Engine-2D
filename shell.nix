with import <nixpkgs> {};
  stdenv.mkDerivation {
    name = "game-engine";
    hardeningDisable = [ "all" ];
    nativeBuildInputs = with pkgs; [
      pkg-config
      gcc
      gnumake
      cmake
      ninja
      clang-tools
      valgrind
    ];
    buildInputs = with pkgs.buildPackages; [
      spdlog
      sfml
      jsoncpp
    ];
  }
