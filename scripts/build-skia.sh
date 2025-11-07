pushd external/skia

python3 tools/git-sync-deps --config="angle_gl_es2"

bin/gn gen out/Static --args='is_official_build=false skia_use_angle=true'

ninja -C out/Static

popd