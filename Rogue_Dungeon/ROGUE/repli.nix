{ pkgs }: {
  deps = [
    pkgs.gcc
    pkgs.mpg123
    pkgs.make
  ];

  shellHook = ''
    echo "Nix environment loaded"
  '';
}