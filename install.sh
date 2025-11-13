#!/bin/bash

APP_NAME="SkyDungeon"
EXECUTABLE="./app"
INSTALL_DIR="$HOME/.local/bin"
DESKTOP_FILE="$HOME/.local/share/applications/${APP_NAME}.desktop"
LAUNCHER="$INSTALL_DIR/launch-${APP_NAME}.sh"

mkdir -p "$INSTALL_DIR"

# Copy game binary
cp "$EXECUTABLE" "$INSTALL_DIR/$APP_NAME"
chmod +x "$INSTALL_DIR/$APP_NAME"

# Create launcher script
cat > "$LAUNCHER" <<EOF
#!/bin/bash
kitty --title "SkyDungeon" \
  --override "initial_window_width=990" \
  --override "initial_window_height=530" \
  --override "remember_window_size=no" \
  "$HOME/.local/bin/SkyDungeon"
EOF
chmod +x "$LAUNCHER"

# Create desktop entry
mkdir -p "$(dirname "$DESKTOP_FILE")"
cat > "$DESKTOP_FILE" <<EOF
[Desktop Entry]
Type=Application
Name=$APP_NAME
Exec=$LAUNCHER
Terminal=true
Categories=Game;
EOF

update-desktop-database ~/.local/share/applications 2>/dev/null || true

echo "Installed $APP_NAME!"

