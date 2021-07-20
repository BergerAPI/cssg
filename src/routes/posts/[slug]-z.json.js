import fs from 'fs'
import frontMatter from "front-matter";

export async function get({ params }) {
    const { content, ...meta } = frontMatter(
        fs.readFileSync("static/posts/" + params.slug + ".md", "utf8"));

    return {
        body: {
            content: content,
            meta: meta
        }
    }
}