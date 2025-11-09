pushd external/skia

python3 tools/git-sync-deps

bin/gn gen out/Static --args='is_official_build=false'

ninja -C out/Static

popd