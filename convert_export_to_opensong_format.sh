#!/bin/bash
#
# OpenSong XML Conversion Script (Lyricue to OpenSong)
#
# This script converts an XML file (compressed or uncompressed) exported from Lyricue
# into separate, standardized OpenSong XML files (one per song) using xmlstarlet and XSLT.
# Enables import into other applications which support OpenSong files such as FreeShow
#
# Required tools: 'xmlstarlet', 'zcat' (if input file is compressed)
# Usage: ./convert_export_to_opensong_format.sh <input_file.xml|input_file.xmlz> [output_directory]
# Example: ./convert_export_to_opensong_format.sh Downloads.xmlz ./opensong_songs:w

INPUT_FILE="$1"
OUTPUT_DIR="${2:-opensong_output}" # Default output directory is 'opensong_output'

# --- Utility Functions ---

# Function to sanitize the song title for use as a filename (e.g., removes spaces, special chars)
sanitize_filename() {
    local filename="$1"
    # 1. Convert to lowercase
    # 2. Replace spaces/underscores with hyphens
    # 3. Remove any non-alphanumeric characters (except hyphens and dots)
    echo "$filename" | tr '[:upper:]' '[:lower:]' | sed -r 's/[^a-z0-9]+/-/g' | sed -r 's/^-+|-+$//g'
}

# --- Pre-flight Checks ---

if [ -z "$INPUT_FILE" ]; then
    echo "Error: Please provide the input XML file." >&2
    echo "Usage: $0 <input_file.xml|input_file.xmlz> [output_directory]" >&2
    exit 1
fi

if ! command -v xmlstarlet &> /dev/null
then
    echo "Error: xmlstarlet could not be found." >&2
    echo "Please install it (e.g., sudo apt install xmlstarlet or brew install xmlstarlet)." >&2
    exit 1
fi

# Check for compression and 'zcat' availability
IS_COMPRESSED=0
if [[ "$INPUT_FILE" == *.xmlz ]] || [[ "$INPUT_FILE" == *.gz ]]; then
    IS_COMPRESSED=1
    if ! command -v zcat &> /dev/null
    then
        echo "Error: Input file is compressed (.xmlz/.gz) but 'zcat' could not be found." >&2
        echo "Please install gzip/zcat." >&2
        exit 1
    fi
fi

# Define the command to read the XML content (either zcat or cat)
if [ "$IS_COMPRESSED" -eq 1 ]; then
    READER_CMD="zcat"
    echo "Input file is compressed. Using zcat to decompress on the fly."
else
    READER_CMD="cat"
    echo "Input file is uncompressed. Using cat."
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"
echo "Output will be saved to: $OUTPUT_DIR"

# --- XSLT Stylesheet Definition (Single Song Conversion) ---

# This XSLT assumes it is applied to a single <song> block (from the lyricue file)
# and transforms it into the OpenSong XML format.

XSLT_SINGLE_SONG=$(cat <<'EOT'
<xsl:stylesheet version="1.0" 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    
  <xsl:output method="xml" indent="yes" encoding="UTF-8"/>
  
  <!-- Root template: The input will be a single <song> element. -->
  <xsl:template match="/song">
    <song>
      <title><xsl:value-of select="name"/></title>
      <author><xsl:value-of select="normalize-space(artist)"/></author> 
      <copyright><xsl:value-of select="normalize-space(copyright)"/></copyright>
      <ccli></ccli>
      
      <!-- OpenSong combines all verses into a single <lyrics> block -->
      <lyrics type="verse">
        <xsl:for-each select="page">
          <!-- Insert Verse Identifier (e.g., [V1]) -->
          <xsl:text>[V</xsl:text>
          <xsl:value-of select="position()"/>
          <xsl:text>]</xsl:text>
          <xsl:text>&#xa;</xsl:text> <!-- Newline after identifier -->

          <!-- Insert Page Content (Lyrics) -->
          <xsl:value-of select="."/>
          <xsl:text>&#xa;&#xa;</xsl:text> <!-- Double newline to separate verses -->
        </xsl:for-each>
      </lyrics>
      
      <!-- Mapping other fields and setting OpenSong defaults -->
      <songbook><xsl:value-of select="book"/></songbook>
      <hymn_no><xsl:value-of select="number"/></hymn_no>
      <keywords><xsl:value-of select="keywords"/></keywords>
      <tempo>0</tempo>
      <theme>General</theme>
      <presentation></presentation>
      <ccli_song_id>0</ccli_song_id>
      <capo>0</capo>
      <key>C</key>
      <user></user>
      <scripture></scripture>
      <version>1</version>
      <tempo_type>none</tempo_type>
      <timesignature>4/4</timesignature>
      <v_order></v_order>
      <notes></notes>
    </song>
  </xsl:template>
  
  <!-- Suppress output of any extraneous text nodes -->
  <xsl:template match="text()"/> 

</xsl:stylesheet>
EOT
)

# --- Execution Loop ---

# Set a temporary file for intermediate song XML data
TEMP_SONG_FILE=$(mktemp)

# 1. Get titles by piping the file content (decompressed or raw) into xmlstarlet
# The hyphen '-' tells xmlstarlet to read from standard input.
TITLES=$("$READER_CMD" "$INPUT_FILE" | xmlstarlet sel -t -v "//lyricue/song/name" -n -)

# Loop through each song found
echo "$TITLES" | while IFS= read -r TITLE; do
    if [ -n "$TITLE" ]; then
        
        # 1. Sanitize the title to create a safe filename
        SAFE_TITLE=$(sanitize_filename "$TITLE")
        OUTPUT_FILE="$OUTPUT_DIR/${SAFE_TITLE}.xml"

        echo "Processing: '$TITLE' -> $OUTPUT_FILE"

        # 2. Extract the *single* song XML block and save it to the temporary file
        # Pipe the file content again, filtering for the specific song by name.
        $READER_CMD "$INPUT_FILE" | xmlstarlet sel -t -c "//lyricue/song[name='$TITLE']" - > "$TEMP_SONG_FILE" 

        # 3. Apply the single-song XSLT to the temporary file
        xmlstarlet tr <(echo "$XSLT_SINGLE_SONG") "$TEMP_SONG_FILE" > "$OUTPUT_FILE"

    fi
done

# Clean up the temporary file
rm "$TEMP_SONG_FILE"

echo "Conversion complete. Files saved in $OUTPUT_DIR."

